import os
from PIL import Image
import mido     

TRANSPARENT = 0xFF

resourcesH = '..\\Kernel\\Resources.h'
with open(resourcesH, 'w') as file:
    file.write('#pragma once\n') #Clear Resources.h

resourcesCpp = '..\\Kernel\\Resources.cpp'
with open(resourcesCpp, 'w') as file:
    file.write('#include "Kernel.h"') #Clear Resources.cpp

for name in os.listdir():
    if name.endswith('.png'): #Embed pictures        
        img = Image.open(name).convert('RGBA')
        name = os.path.splitext(name)[0]
        
        colors = []
        
        w, h = img.size
        for y in range(h):
            for x in range(w):
                r, g, b, a = img.getpixel((x, y))
            
                if a < 64:
                    colors.append(TRANSPARENT)
                    continue
            
                #Encode pixel color
                r = int(r / 255 * 5)
                g = int(g / 255 * 5)
                b = int(b / 255 * 5)
                
                colors.append(r * 36 + g * 6 + b)

        compressed = [colors[0]]
        n = 0

        for i in range(1, len(colors)):
            if colors[i] == compressed[-1] and n < 255:
                n += 1
            else:
                compressed += [n, colors[i]]
                n = 0
        compressed.append(n)
        
        with open(resourcesH, 'a+') as file:
            file.write(f'\nextern Picture {name};')             
        
        with open(resourcesCpp, 'a+') as file:
            file.write(f'\n\nuint8_t {name}_pixelData[] = {{')
            file.write(', '.join(hex(i) for i in compressed))
            file.write('};')
            file.write(f'\nPicture {name} = {{{w}, {h}, {name}_pixelData, NULL, 0}};')
    
    elif name.endswith('.mid'): #Embed midis
        midi = mido.MidiFile(name)
        name = os.path.splitext(name)[0]
        
        notes = []  
        tempo = 500000 #Start from 120 BPM
        
        for msg in midi.tracks[0]: #Look for tempo in time track
            if msg.type == 'set_tempo':
                tempo = msg.tempo
                break #TEMPO CHANGE IS NOT SUPPORTED!!!
        
        for msg in midi.tracks[1]: #Only the first track (track[0] is the time track)
            timeDelta = mido.tick2second(msg.time, midi.ticks_per_beat, tempo) * 100
            
            if msg.type == 'note_on' and msg.velocity > 0:
                notes.append(timeDelta)
                notes.append(440 * 2 ** ((msg.note - 69) / 12))
            elif msg.type == 'note_off' or (msg.type == 'note_on' and msg.velocity == 0): 
                notes.append(timeDelta)
                notes.append(0) 
        
        notes.pop() #Remove last note_off message
        
        with open(resourcesH, 'a+') as file:
            file.write(f'\nextern Music {name};')             
        
        with open(resourcesCpp, 'a+') as file:
            file.write(f'\n\nuint16_t {name}_musicData[] = {{0x0, ')
            file.write(', '.join(hex(int(i)) for i in notes))
            file.write(f'}};\nMusic {name} = {{{(len(notes) + 1) // 2}, {name}_musicData}};')
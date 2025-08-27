#pip install colour-science
#pip install pillow

import colour
import colorsys
from PIL import Image, ImageDraw

def Rgb2Lab(rgb):
    return colour.models.XYZ_to_Oklab(colour.models.sRGB_to_XYZ(rgb)) 

def Lab2Rgb(lab):
    return colour.models.XYZ_to_sRGB(colour.models.Oklab_to_XYZ(lab)) 
    
def DeltaE(lab1, lab2, lWeight = 5.0):
    l1, a1, b1 = lab1
    l2, a2, b2 = lab2
    return ((lWeight * (l1 - l2)) ** 2 + (a1 - a2) ** 2 + (b1 - b2) ** 2) ** 0.5

colorWheel = []
totalDeltaE = 0

for i in range(360):
    colorWheel.append(colorsys.hsv_to_rgb(i / 360, 1, 1))

firstColor = Rgb2Lab(colorWheel[0])

for i in range(360):
    dE = DeltaE(Rgb2Lab(colorWheel[i]), firstColor if i + 1 >= 360 else Rgb2Lab(colorWheel[i + 1]))
    colorWheel[i] = (colorWheel[i], dE)
    totalDeltaE += dE

number = 10

colors = []
j = 0
dE = 0

for i in range(number):
    while dE < totalDeltaE / number * i:
        j += 1
        dE += colorWheel[j % 360][1]
    
    colors.append(tuple([int(c * 255) for c in colorWheel[j][0]]))
    print(f'#{colors[i][0]:02X}{colors[i][1]:02X}{colors[i][2]:02X}')

width, height = 800, 100
stripeWidth = width // number

img = Image.new('RGB', (width, height))
draw = ImageDraw.Draw(img)

for i, color in enumerate(colors):
    x0 = i * stripeWidth
    x1 = x0 + stripeWidth
    draw.rectangle([x0, 0, x1, height], fill = color)

img.show()
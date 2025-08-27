for i in range(32, 256):
    print(f'ISR_NOERROR {i}')

for i in range(256):
    print(f'extern "C" void ISR{i}();')

for i in range(256):
    print(f'IDT_SetGate({i}, (uint64_t)ISR{i}, CODE_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);')
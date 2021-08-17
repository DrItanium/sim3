            X(0x080, b)
            X(0x090, call)
            X(0x0A0, ret)
            X(0x0B0, bal)
            X(0x100, bno)
            X(0x110, bg)
            X(0x120, be)
            X(0x130, bge)
            X(0x140, bl)
            X(0x150, bne)
            X(0x160, ble)
            X(0x170, bo)
            X(0x180, faultno)
            X(0x190, faultg)
            X(0x1A0, faulte)
            X(0x1B0, faultge)
            X(0x1C0, faultl)
            X(0x1D0, faultne)
            X(0x1E0, faultle)
            X(0x1F0, faulto)
            X(0x200, testno)
            X(0x210, testg)
            X(0x220, teste)
            X(0x230, testge)
            X(0x240, testl)
            X(0x250, testne)
            X(0x260, testle)
            X(0x270, testo)
            X(0x300, bbc)
            X(0x310, cmpobg)
            X(0x320, cmpobe)
            X(0x330, cmpobge)
            X(0x340, cmpobl)
            X(0x350, cmpobne)
            X(0x360, cmpoble)
            X(0x370, bbs)
            X(0x380, cmpibno)
            X(0x390, cmpibg)
            X(0x3A0, cmpibe)
            X(0x3B0, cmpibge)
            X(0x3C0, cmpibl)
            X(0x3D0, cmpibne)
            X(0x3E0, cmpible)
            X(0x3F0, cmpibo)

            X(0x580, notbit)
            X(0x581, logicalAnd)
            X(0x582, andnot)
            X(0x583, setbit)
            X(0x584, notand )
            X(0x586, logicalXor )
            X(0x587, logicalOr )
            X(0x588, logicalNor )
            X(0x589, logicalXnor )
            X(0x58A, logicalNot )
            X(0x58B, ornot )
            X(0x58C, clrbit )
            X(0x58D, notor )
            X(0x58E, logicalNand )
            X(0x58F, alterbit )
            X(0x590, addo)
            X(0x591, addi)
            X(0x592, subo)
            X(0x593, subi )
            X(0x594, cmpob)
            X(0x595, cmpib)
            X(0x596, cmpos)
            X(0x597, cmpis)
            X(0x598, shro)
            X(0x59A, shrdi)
            X(0x59B, shri)
            X(0x59C, shlo)
            X(0x59D, rotate)
            X(0x59E, shli)
            X(0x5A0, cmpo)
            X(0x5A1, cmpi)
            X(0x5A2, concmpo)
            X(0x5A3, concmpi)
            X(0x5A4, cmpinco)
            X(0x5A5, cmpinci)
            X(0x5A6, cmpdeco)
            X(0x5A7, cmpdeci)
            X(0x5AC, scanbyte)
            X(0x5AD, bswap)
            X(0x5AE, chkbit)
            X(0x5B0, addc)
            X(0x5B2, subc)
            X(0x5B4, intdis)
            X(0x5B5, inten)
            X(0x5CC, mov)
            X(0x5D8, eshro)
            X(0x5DC, movl)
            X(0x5EC, movt)
            X(0x5FC, movq)
            X(0x610, atmod)
            X(0x612, atadd)
            X(0x640, spanbit)
            X(0x641, scanbit)
#ifdef NUMERICS_ARCHITECTURE
            X(0x642, daddc)
            X(0x643, dsubc)
            X(0x644, dmovt)
#endif
            X(0x645, modac)
            X(0x650, modify)
            X(0x651, extract)
            X(0x654, modtc)
            X(0x655, modpc)
            X(0x658, intctl)
            X(0x659, sysctl)
            X(0x65B, icctl)
            X(0x65C, dcctl)
            X(0x660, calls)
            X(0x66B, mark)
            X(0x66C, fmark)
            X(0x66D, flushreg)
            X(0x66F, syncf)
            X(0x670, emul)
            X(0x671, ediv)
            X(0x701, mulo)
            X(0x708, remo)
            X(0x70B, divo)
            X(0x741, muli)
            X(0x748, remi)
            X(0x749, modi)
            X(0x74B, divi)
            X(0x780, addono )
            X(0x781, addino )
            X(0x782, subono )
            X(0x783, subino )
            X(0x784, selno )
            X(0x790, addog )
            X(0x791, addig )
            X(0x792, subog )
            X(0x793, subig )
            X(0x794, selg )
            X(0x7A0, addoe )
            X(0x7A1, addie )
            X(0x7A2, suboe )
            X(0x7A3, subie )
            X(0x7A4, sele )
            X(0x7B0, addoge )
            X(0x7B1, addige )
            X(0x7B2, suboge )
            X(0x7B3, subige )
            X(0x7B4, selge )
            X(0x7C0, addol )
            X(0x7C1, addil )
            X(0x7C2, subol )
            X(0x7C3, subil )
            X(0x7C4, sell )
            X(0x7D0, addone)
            X(0x7D1, addine)
            X(0x7D2, subone)
            X(0x7D3, subine)
            X(0x7D4, selne)
            X(0x7E0, addole)
            X(0x7E1, addile)
            X(0x7E2, subole)
            X(0x7E3, subile)
            X(0x7E4, selle)
            X(0x7F0, addoo)
            X(0x7F1, addio)
            X(0x7F2, suboo)
            X(0x7F3, subio)
            X(0x7F4, selo)
            X(0x800, ldob)
            X(0x820, stob)
            X(0x840, bx)
            X(0x850, balx)
            X(0x860, callx)
            X(0x880, ldos)
            X(0x8A0, stos)
            X(0x8C0, lda)
            X(0x900, ld)
            X(0x920, st )
            X(0x980, ldl)
            X(0x9A0, stl)
            X(0xA00, ldt)
            X(0xA20, stt)
            X(0xB00, ldq)
            X(0xB20, stq)
            X(0xC00, ldib)
            X(0xC20, stib)
            X(0xC80, ldis)
            X(0xCA0, stis)
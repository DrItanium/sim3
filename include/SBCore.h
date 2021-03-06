// sim3
// Copyright (c) 2021, Joshua Scoggins
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Created by jwscoggins on 8/21/21.
//

#ifndef SIM3_SBCORE_H
#define SIM3_SBCORE_H
#ifdef DESKTOP_BUILD
#include "DesktopSBCore.h"
#elif defined(ARDUINO_NRF52832_FEATHER)
#include "NRF52832FeatherSBCore.h"
#elif defined(ARDUINO_GRAND_CENTRAL_M4)
#include "GCM4SBCore.h"
#elif defined(ARDUINO_FEATHER_M0_ADALOGGER)
#include "FeatherM0AdaloggerSBCore.h"
#elif defined(ARDUINO_AVR_ATmega1284)
#include "1284pSBCore.h"
#elif defined(ARDUINO_AVR_MEGA2560)
#include "Mega2560SBCore.h"
#else
#error "NO VALID SBCORE IMPLEMENTATION FOR GIVEN TARGET"
#endif
#endif //SIM3_SBCORE_H

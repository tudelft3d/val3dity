#ifndef VAL3DITY_INPUT_DEFINITIONS_H
#define VAL3DITY_INPUT_DEFINITIONS_H

/*
 val3dity - Copyright (c) 2011-2012, Hugo Ledoux.  All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of the authors nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL HUGO LEDOUX BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*/

// We are currently only including this to get the definition of polyhedraShell.
#include "validate.h"



// This callback function will be used to both report progress
// as well as any validity problems that are encountered.
typedef void (* cbf)(Val3dity_ErrorCode errorCode,    // 0 means status message, -1 means unknown error
                     int shellNum, // -1 means unused
                     int facetNum,     // -1 means unused
                     std::string messageStr); // optional


// -----------------------------------------------------------
// Usage documentation for this method goes here.
//
// Ignore the first value in the array filenames for now...
void readAllInputShells(vector<string> &arguments, vector<Shell*> &shells, cbf cb);
void readAllInputShells_withIDs(vector<string> &arguments, vector<Shell*> &shells, vector<string> &idShells, vector< vector<string> > &idFaces, cbf cb);

#endif

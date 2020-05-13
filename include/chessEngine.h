#ifndef CHESSENGINE_H
#define CHESSENGINE_H

#if defined (__WIN32)
#include "utils.h"
#include "pieces.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

STARTUPINFO sti = {0};
SECURITY_ATTRIBUTES sats = {0};
PROCESS_INFORMATION pi = {0};
HANDLE pipin_w, pipin_r, pipout_w, pipout_r;
BYTE buffer[100010];
DWORD writ, excode, read, available;


void ConnectToEngine(char* path)
{
    pipin_w = pipin_r = pipout_w = pipout_r = NULL;
    sats.nLength = sizeof(sats);
    sats.bInheritHandle = TRUE;
    sats.lpSecurityDescriptor = NULL;

    CreatePipe(&pipout_r, &pipout_w, &sats, 0);
    CreatePipe(&pipin_r, &pipin_w, &sats, 0);

    sti.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    sti.wShowWindow = SW_HIDE;
    sti.hStdInput = pipin_r;
    sti.hStdOutput = pipout_w;
    sti.hStdError = pipout_w;

    CreateProcess(NULL, path, NULL, NULL, TRUE,0, NULL, NULL, &sti, &pi);

}


std::pair <Square, Square> getStockfishMove(std::string position, PieceType &newPiece)
{
    std::string str;
    position = "position startpos moves " + position + "\ngo depth 10\n";

    WriteFile(pipin_w, position.c_str(), position.length(),&writ, NULL);
    Sleep(500);

    PeekNamedPipe(pipout_r, buffer,sizeof(buffer), &read, &available, NULL);
    do
    {
        ZeroMemory(buffer, sizeof(buffer));
        if(!ReadFile(pipout_r, buffer, sizeof(buffer), &read, NULL) || !read) break;
        buffer[read] = 0;
        str += (char*)buffer;
    }
    while(read >= sizeof(buffer));
    // This is very unsafe! Stockfish is shit and doesn't print bestmove every time.
    int n = str.find("bestmove");
    std::string aux = str.substr(n + 9,4);
    if (str[n + 13] >= 'a' && str[n + 13] <= 'z') {
        if (str[n + 13] == 'q') newPiece = QUEEN;
        else if (str[n + 13] == 'r') newPiece = ROOK;
        else if (str[n + 13] == 'b') newPiece = BISHOP;
        else if (str[n + 13] == 'k') newPiece = KNIGHT;
    }
    return {my_notation_pos(aux.substr(0, 2)), my_notation_pos(aux.substr(2, 2))};
}


void CloseConnection()
{
    WriteFile(pipin_w, "quit\n", 5,&writ, NULL);
    if(pipin_w != NULL) CloseHandle(pipin_w);
    if(pipin_r != NULL) CloseHandle(pipin_r);
    if(pipout_w != NULL) CloseHandle(pipout_w);
    if(pipout_r != NULL) CloseHandle(pipout_r);
    if(pi.hProcess != NULL) CloseHandle(pi.hProcess);
    if(pi.hThread != NULL) CloseHandle(pi.hThread);
}
#else
#include "utils.h"
#include <fstream>
#include <cstdlib>
#include <assert.h>

void ConnectToEngine(const std::string &s) {
    std::string t = s;
    t.clear();
}
void CloseConnection() {}

std::pair <Square, Square> getStockfishMove(const std::string position, PieceType &newPiece) {
    std::ofstream fout("../script/buffer.txt");
    fout << position;
    fout.close();
    
    assert(!system("python3 ../script/script.py"));

    std::ifstream fin("../script/buffer.txt");
    std::string s;
    fin >> s;
    fin.close();

    if (s.size() == 5) {
        if (s[4] == 'q') newPiece = QUEEN;
        else if (s[4] == 'r') newPiece = ROOK;
        else if (s[4] == 'b') newPiece = BISHOP;
        else if (s[4] == 'k') newPiece = KNIGHT;
    }

    return std::make_pair(my_notation_pos(s.substr(0, 2)), my_notation_pos(s.substr(2, 2)));
}

#endif

#endif
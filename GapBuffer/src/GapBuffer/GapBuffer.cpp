#include "GapBuffer/GapBuffer.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

GapBuffer::GapBuffer(int initialSize) 
    : buffer(initialSize, '\0')
    , gapStart(0)
    , gapEnd(initialSize) 
{

} 

void GapBuffer::insert(char c)
{
    buffer[gapStart++] = c;
    
    if (gapStart == gapEnd) {
        resize();
    }
}

void GapBuffer::insert(const std::string& str)
{
    for (char c : str) {
        insert(c);
    }
}

void GapBuffer::moveLeft()
{
    if (gapStart == 0) {
        return;
    }

    buffer[gapEnd - 1] = buffer[gapStart - 1];

    gapStart--;
    gapEnd--;
}

void GapBuffer::moveRight()
{
    if (gapEnd == buffer.size()) {
        return;
    }

    buffer[gapStart] = buffer[gapEnd];

    gapStart++;
    gapEnd++;
}

void GapBuffer::resize()
{
    int suffixLen = buffer.size() - gapEnd;
    int oldSize = buffer.size();
    
    buffer.resize(buffer.size() * 2, '\0');

    for (int i = gapEnd; i < oldSize; i++) {
        buffer[buffer.size() - suffixLen + i - gapEnd] = buffer[i];
    }

    gapEnd = buffer.size() - suffixLen;
}

void GapBuffer::moveWordLeft() 
{
    if (gapStart > 0 && (buffer[gapStart - 1] == ' ' || buffer[gapStart - 1] == '\n')) {
        moveLeft();
    }

    while (gapStart > 0 && buffer[gapStart - 1] != ' ' && buffer[gapStart - 1] != '\n') {
        moveLeft();
    }
}

void GapBuffer::moveWordRight() 
{
    if (gapEnd < buffer.size() && (buffer[gapEnd] == ' ' || buffer[gapEnd] == '\n')) {
        moveRight();
    }

    while (gapEnd < buffer.size() && buffer[gapEnd] != ' ' && buffer[gapEnd] != '\n') {
        moveRight();
    }
}

void GapBuffer::moveToStart() 
{
    int oldPos = gapStart;
    gapStart = 0;
    
    while (gapStart > 0) {
        moveLeft();
    }
}

void GapBuffer::moveToEnd() 
{
    int oldPos = gapStart;
    
    while (gapEnd < buffer.size()) {
        moveRight();
    }
}

char GapBuffer::getCharAt(int idx)
{
    // just return null char if out of bounds
    if (idx < 0) {
        return '\0';
    }
    else if (idx >= totalChars()) {
        return '\0';
    }

    if (idx < gapStart) {
        return buffer[idx];
    } 
    else {
        return buffer[gapEnd + idx - gapStart];
    }
}

int GapBuffer::getCursor()
{
    return gapStart;
}

void GapBuffer::backSpace()
{
    if (gapStart == 0) {
        return;
    }

    buffer[gapStart-1] = '\0';
    gapStart--;
}

void GapBuffer::backSpaceWord()
{
    backSpace();

    while (gapStart > 0 && buffer[gapStart - 1] != ' ' && buffer[gapStart - 1] != '\n') {
        backSpace();
    }
}

void GapBuffer::deleteChar()
{
    if (gapEnd == buffer.size()) {
        return;
    }
    
    buffer[gapEnd] = '\0';
    gapEnd++;
}

void GapBuffer::deleteWord()
{
    deleteChar();

    while (gapEnd < buffer.size() && buffer[gapEnd] != ' ' && buffer[gapEnd] != '\n') {
        deleteChar();
    }
}

int GapBuffer::totalChars()
{
    return gapStart + (buffer.size() - gapEnd);
}

void GapBuffer::clearBuffer()
{
    clearBuffer(DEFAULT_BUF_SIZE);  
}

void GapBuffer::clearBuffer(int initialSize)
{
    buffer.clear();
    buffer.resize(initialSize, '\0');
    gapStart = 0;
    gapEnd = buffer.size();
}

GapBuffer::~GapBuffer() 
{
    clearBuffer(0);
}
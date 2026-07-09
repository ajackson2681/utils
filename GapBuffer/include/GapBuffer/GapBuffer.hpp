#pragma once

#include <vector>
#include <string>
#include <cstdint>

#define DEFAULT_BUF_SIZE 8192

#define SHOW_GAP false

class GapBuffer 
{
public:
    GapBuffer(int initialSize = DEFAULT_BUF_SIZE);
    virtual ~GapBuffer();

    /**
     * @brief insert a character at the current cursor position. This will 
     * resize the buffer if necessary.
     * 
     * @param c Character to insert
     */
    virtual void insert(char c);
    
    /**
     * @brief insert a string at the current cursor postion. This will resize
     * the buffer if necessary.
     * 
     * @param str String to insert
     */
    virtual void insert(const std::string& str);

    /**
     * @brief Moves the cursor left by one character
     */
    virtual void moveLeft();
    
    /**
     * @brief Moves the cursor right by one character
     */
    virtual void moveRight();

    /**
     * @brief Moves the cursor left by one word. A "word" in this case is
     * defined as a space-separated value
     */
    virtual void moveWordLeft();

    /**
     * @brief Moves the cursor right by one word. A "word" in this case is
     * defined as a space-separated value
     */
    virtual void moveWordRight();

    /**
     * @brief Moves the cursor to the very beginning of the buffer
     */
    virtual void moveToStart();

    /**
     * @brief Moves the cursor to the very end of the buffer
     */
    virtual void moveToEnd();

    /**
     * @brief Deletes the character to the left of the cursor
     */
    virtual void backSpace();

    /**
     * @brief Deletes the word to the left of the cursor. A "word" in this case 
     * is defined as a space-separated value.
     */
    virtual void backSpaceWord();

    /**
     * @brief Deletes the character to the right of the cursor
     */
    virtual void deleteChar();

    /**
     * @brief Deletes the word to the right of the cursor. A "word" in this case 
     * is defined as a space-separated value.
     */
    virtual void deleteWord();
    
    /**
     * @brief Returns the character at the specified index in the buffer. 
     * This index is relative to the start of the buffer, not the gap.
     * 
     * @param idx Index of the character to retrieve
     * @return char Character at the specified index, or '\0' if the index is 
     * out of bounds
     */
    virtual char getCharAt(int idx);

    /**
     * @brief Returns the current cursor position in the buffer. This is just
     * the index of the gap start.
     * 
     * @return int Current cursor position
     */
    virtual int getCursor();

    /**
     * @brief Total characters in the buffer, not the size of the buffer vector
     * 
     * @return int Number of characters inserted into the buffer
     */
    virtual int totalChars();

    /**
     * @brief Empties the buffer and returns it to its initial state. Uses the 
     * default initial size.
     */
    void clearBuffer();

    /**
     * @brief Empties the buffer and returns it to its initial state. Uses the 
     * specified initial size.
     * 
     * @param initialSize Initial size of the buffer
     */
    void clearBuffer(int initialSize);

protected:
    std::vector<char> buffer;
    int gapStart;
    int gapEnd;    
    
    /**
     * @brief Resizes the buffer vector. It will double in size with each
     * call to this. If you wish to set size constraints, you can override this
     * method in a derived class and implement your own resizing logic.
     */
    virtual void resize();
};
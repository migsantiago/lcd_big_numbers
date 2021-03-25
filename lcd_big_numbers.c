/**
 * Original code: https://gist.github.com/ronivaldo/5587355
 *
 * Cleaned up code: https://github.com/migsantiago/lcd_big_numbers
 * This is only a snippet. Adapt this code to your own LCD code :D
 */

/**
 * Draw a character manually by sending 8 bytes
 * @param address - choose user char from 0 to 7
 * @param rows - pass an array of 8 bytes to draw a char
 */
void lcd_set_cg_char(const LCD_CGRAM_Address_T address, const uint8_t* rows);

/**
 * The user can draw big numbers on the LCD by calling this function
 */
void lcd_init_big_numbers(void);

/**
 * Draw a big number (2 rows, 3 columns)
 * @param number - 0 to 9
 * @param row - row to set
 * @param column - column to set
 */
void lcd_set_big_number(const uint8_t number, const uint8_t row, const uint8_t column);

void lcd_set_cg_char(const LCD_CGRAM_Address_T address, const uint8_t* rows)
{
    lcd_send_cmd(address);
    for (size_t count = 0; count < BYTES_PER_CG_CHAR; ++count)
    {
        lcd_send_data(rows[count]);
    }
}

void lcd_init_big_numbers(void)
{
    // Table for big chars for numbers
    // Adapted from https://gist.github.com/ronivaldo/5587355
    static const uint8_t BIG_NUMBER[8][8] =
    {
        {0b11100, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11100},
        {0b00111, 0b01111, 0b01111, 0b01111, 0b01111, 0b01111, 0b01111, 0b00111},
        {0b11111, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111},
        {0b11110, 0b11100, 0b00000, 0b00000, 0b00000, 0b00000, 0b11000, 0b11100},
        {0b01111, 0b00111, 0b00000, 0b00000, 0b00000, 0b00000, 0b00011, 0b00111},
        {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111},
        {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00111, 0b01111},
        {0b11111, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    };

    lcd_set_cg_char(CGRAM_CHAR1, &BIG_NUMBER[0][0]);
    lcd_set_cg_char(CGRAM_CHAR2, &BIG_NUMBER[1][0]);
    lcd_set_cg_char(CGRAM_CHAR3, &BIG_NUMBER[2][0]);
    lcd_set_cg_char(CGRAM_CHAR4, &BIG_NUMBER[3][0]);
    lcd_set_cg_char(CGRAM_CHAR5, &BIG_NUMBER[4][0]);
    lcd_set_cg_char(CGRAM_CHAR6, &BIG_NUMBER[5][0]);
    lcd_set_cg_char(CGRAM_CHAR7, &BIG_NUMBER[6][0]);
    lcd_set_cg_char(CGRAM_CHAR8, &BIG_NUMBER[7][0]);
}

void lcd_set_big_number(const uint8_t number, const uint8_t row, const uint8_t column)
{
    static const uint8_t BIG_NUMBER_CELLS[10][6] =
    {
        {1, 7, 0, 1, 5, 0},             // 0
        {' ', ' ', 0, ' ', ' ', 0},     // 1
        {4, 2, 0, 1, 5, 5},             // 2
        {4, 2, 0, 6, 5, 0},             // 3
        {1, 5, 0, ' ', ' ', 0},         // 4
        {1, 2, 3, 6, 5, 0},             // 5
        {1, 2, 3, 1, 5, 0},             // 6
        {1, 7, 0, ' ', ' ', 0},         // 7
        {1, 2, 0, 1, 5, 0},             // 8
        {1, 2, 0, 6, 5, 0},             // 9
    };

    lcd_set_coordinate(row,  column);
    lcd_send_data(BIG_NUMBER_CELLS[number][0]);
    lcd_send_data(BIG_NUMBER_CELLS[number][1]);
    lcd_send_data(BIG_NUMBER_CELLS[number][2]);

    lcd_set_coordinate(row + 1,  column);
    lcd_send_data(BIG_NUMBER_CELLS[number][3]);
    lcd_send_data(BIG_NUMBER_CELLS[number][4]);
    lcd_send_data(BIG_NUMBER_CELLS[number][5]);
}

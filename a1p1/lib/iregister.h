//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.

#ifndef lab0_iregister_h
#define lab0_iregister_h

/**
 *  iRegister
 *  An iRegister is a structure which represents an 32-bit register and
 *  is equipped with standard operations to modify and display them.
 */
typedef struct {
    int content;
} iRegister;

/**
 *  Bellow you find the declarations for the functions to modify and display the
 *  memory content of a iRegister data structure. Before each declaration, a
 * brief description about what the function shall do is given. Later in this
 * file, the documentation for the resetBit function is given. Students should
 * follow that format.
 */

/** @brief resets all the bits of the iRegister (to 0)
 *
 * @param r A pointer to a memory location of a iRegister data structure
 *
 * @return void
 *
 * Pre-condition: iRegister != Null
 *
 * Post-condition: r has all of its bits set to 0
 *
 * Properties:
 * after resetAll(r), getBit(j, r) = 0 for all 0 <= j < 32
 */
void resetAll(iRegister *);

/** @brief sets the i'th bit of the iRegister (to 1)
 *
 * @param i The ith position to change
 *
 * @param r A pointer to a memory location of a iRegister data structure
 *
 * @return void
 *
 * Pre-condition: 0 <= i < 32 and iRegister != Null
 *
 * Post-condition: r has its ith bit set to 1, all other remain unchanged
 *
 * Properties:
 * after setBit(i, r), getBit(i, r) = 1
 *
 */
void setBit(int, iRegister *);

/** @brief sets all the bits of the iRegister (to 1)
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 *
 * @return void
 *
 * Pre-condition: iRegister != Null
 *
 * Post-condition: r has all of its bits set to one
 *
 * Properties:
 * after resetAll(r), getBit(j, r) = 1 for all 0 <= j < 32
 */
void setAll(iRegister *);

/** @brief returns the i'th bit of the iRegister as an integer (1 if it is set,
 * or 0 otherwise)
 *
 * @param i The ith bit to return as an integer
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 *
 * @return int The value of the bit
 *
 * Pre-condition: 0 <= i < 32 and iRegister != Null
 *
 * Post-condition: The return value is either 0 or 1, and iRegister is left
 * unchanged
 *
 * Properties:
 * if the ith bit of i = 0:
 * 0 is returned
 * else:
 * 1 is returned
 * with 0 <= i < 32
 */
int getBit(int, iRegister *);

/** @brief set the first (for pos=1) or the second (for pos=2) four bits of
 * iRegsiter
 *
 * @param pos Is either the first or second byte of iRegister
 *
 * @param i The four bits to set to iRegister
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 *
 * @return void
 *
 * Pre-condition: 0 < n <= 2 and iRegister != Null
 *
 * Post-condition: the first or second four bits of iRegister will take the
 * value of the last four bits of i
 *
 * Properties:
 *
 */
void assignNibble(int, int, iRegister *);

/** @brief get the first (for pos=1) or the second (for pos=2) four bits of
 * iRegister
 *
 * @param pos Is either the first or second byte of iRegister
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 *
 * @return int The four bits of iRegister
 *
 * Pre-condition: 0 < n <= 2 and iRegister != Null
 *
 * Post-condition: the return value = first or second four bits of iRegister
 *
 * Properties:
 *
 */
int getNibble(int, iRegister *);

/** @brief returns a pointer to an array of 32 characters, with each character
 *  representing the corresponding bit of the iRegister, i.e., if the bit is
 * set, then the character is "1" (ASCII char with code 49), or otherwise is "0"
 *  (ASCII char with code 48)
 *
 *  @param r A copy variable of a data structure iRegister
 *
 *  @return char * The created string representation of iRegister
 *
 *  Pre-condition: iRegister != Null
 *
 *  Post-condition: char * of length = 32 with only '0' and '1' characters
 *
 *  Properties:
 *  for 0 <= i < 32 and with char * str:
 *  if getBit(i, &r) = 0
 *      str[i] = '0'
 *   else if getBit(i, &r) = 1
 *      str[i] = '1'
 */
char *reg2str(iRegister);

/** @brief shifts all the bits of the iRegister to the right by n palces
 * (appends 0 from the left)
 *
 * @param n Is the number of bits of iRegister to shift to the right
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 *
 * @return void
 *
 * Pre-condition: 0 <= n < 32 and iRegister != Null
 *
 * Post-condition: after shift, iRegister is shifted by nth bits to the right,
 * appending 0 from the left
 *
 * Properties:
 * after shiftRight(n, r), getBit(n, r) = 0
 */
void shiftRight(int, iRegister *);

/** @brief shifts all the bits of the iRegister to the left by n palces (appends
 * 0 from the right)
 *
 * @param n Is the number of bits of iRegister to shift to the left
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 *
 * @return void
 *
 * Pre-condition: 0 <= n < 32 and iRegister != Null
 *
 * Post-condition: after shift, iRegister is shifted by nth bits to the left,
 * appending 0 from the right
 *
 * Properties:
 * after shiftLeft(n, r), getBit(32 - n, r) = 0
 */
void shiftLeft(int, iRegister *);

/** @brief Resets the i'th bit of the iRegister (to 0)
 *
 *  @param i Is i'th bit of the iRegister to be reset
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition: 0 <= i < 32 and iRegister != Null
 *
 *  Post-condition: after reset(i, r) the i'th bit of iRegister is 0, all other
 *  bits remain unchanged
 *  properties:
 *  after resetBit(i, r),  getBit(i, r) = 0
 *  if getBit(i, r) == 0 then
 *    getBit(j, r) returns the same value for all
 *  0 <= j < 32 and j <> i before and after resetBit(i, r)
 *
 *  test-cases:
 *  1,2,3. Allocate memory to an iRegister r
 *  first do resetAll(&r),
 *  then set the i'th bit of &x by setBit(i, &r) for i = 0, 15 and 23 and then
 *  display the result after each and every call by
 *    printf("%s",reg2str(r))
 */
void resetBit(int, iRegister *);

#endif

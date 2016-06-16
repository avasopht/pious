/*
 * Created by The Pious Authors on 12/06/2016.
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef PIOUS_PIOUS_TYPES_H
#define PIOUS_PIOUS_TYPES_H

typedef char Pious_S8;
typedef unsigned char Pious_U8;
typedef short Pious_S16;
typedef unsigned short Pious_U16;
typedef int Pious_S32;
typedef unsigned int Pious_U32;
typedef long long Pious_S64;
typedef unsigned long long Pious_U64;
typedef float Pious_F32;
typedef double Pious_F64;


/*! \struct Pious_DataPacket
 *  \brief  Holds a variable length data packet.
 *
 *  Holds a variable length data packet sent and received by Pious units and
 *  modules.
 */
struct Pious_DataPacket {
  /*! \var    offset
   *  \brief  Batch offset in samples.
   */
  Pious_S32 offset;
  /*! \var    data_length
   *  \brief  Length of data array in bytes.
   */
  Pious_S32 data_length;
  /*! \var    data
   *  \brief  Variable length data.
   */
  char data[4];
};

#endif /*PIOUS_PIOUS_TYPES_H*/

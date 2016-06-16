/*
 * Created by The Pious Authors on 17/06/2016.
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

#ifndef PIOUS_PIOUS_H
#define PIOUS_PIOUS_H

/** Basic types */

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

/** Forward declaration */

struct Pious_Scope;
struct Pious_UnitSpec;
struct Pious_UnitIoSpec;

/** I/o data types */

/*! \struct   Pious_HoldSignalEvent
 *  \brief    Stores a 'hold signal' event.
 */
struct Pious_HoldSignalEvent {
  /*! Batch offset in samples */
  Pious_S32 offset;
  Pious_F32 old_value;
  Pious_F32 new_value;
};

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

/** Pious Unit */

/* Methods PiousUnits will have to implement **/

/*! \typedef  TPious_UnitPluginSpec
 *  \brief    Echoes plugin spec to the scope.
 */
typedef void (*TPious_UnitPluginSpec)(struct Pious_UnitScope *scope);
/*! \typedef  TPious_UnitPluginUnit
 *  \brief    Initializes plugin and returns new data pointer.
 *
 *  Initializes the plugin and returns a new pointer to its data to be used by
 *  the Pious_UnitPluginRender method.
 */
typedef void* (*TPious_UnitPluginInit)(struct Pious_UnitScope *scope);
/*! \typedef  TPious_UnitPluginRender
 *  \brief    Renders output
 */
typedef void (*TPious_UnitPluginRender)(struct Pious_UnitScope *scope, void *data, Pious_S32 frames);


enum /* Pious_UnitConstants */ {
  Pious_UnitNameMax = 256,
  Pious_UnitShortNameMax = 8,
  Pious_UnitIoMax = 2048,
  Pious_UnitIdMax = 128
};

/*! \enum   Pious_UnitIoType
 *  \brief  Describes type of io port on a unit.
 *
 *  Units can input and output signals (audio / continuous control voltage),
 *  hold signals (e.g. gate, parameter changes), and data (midi, etc.).
 *
 *  Future types may include signal and hold signal arrays.
 */
enum Pious_UnitIoType {
  Pious_UnitIoTypeNone,
  Pious_UnitIoTypeSignalIn,
  Pious_UnitIoTypeSignalOut,
  Pious_UnitIoTypeHoldSignalIn,
  Pious_UnitIoTypeHoldSignalOut,
  Pious_UnitIoTypeDataIn,
  Pious_UnitIoTypeDataOut
};


/*! \struct   Pious_UnitIoSpec
 *  \brief    Specification for a Unit I/O port.
 */
struct Pious_UnitIoSpec {
  /*! \var    name
   *  \brief  Full name of io port.
   */
  char name[Pious_UnitNameMax];
  /*! \var    short_name
   *  \brief  Short name of io port.
   */
  char short_name[Pious_UnitShortNameMax];
  /*! \var    iid
   *  \brief  Integer id of port.
   *
   *  Can be zero or negative, indicating no integer id.
   *  IO port must have at least one valid method of id.
   */
  Pious_S32 iid;
  /*! \var    sid
   *  \brief  String id of port.
   *
   *  Can be zero length, indicating no string id.
   *  IO port must have at least one valid method of id.
   */
  char sid[Pious_UnitIdMax];
  /*  \var    io_type
   *  \brief  Type of io.
   *
   *  See Pious_IoType enum for
   */
  char io_type;
};

/*! \struct   Pious_UnitSpec
 *  \brief    Specification for Unit.
 */
struct Pious_UnitSpec {
  char name[Pious_UnitNameMax];
  char short_name[Pious_UnitShortNameMax];
};


/** Pious Scope methods */

/*! \typedef  TPious_GetSampleRate
 *  \brief    Returns samplerate of scope.
 */
typedef float (*TPious_GetSampleRate)(struct Pious_Scope *scope);

/*! \typedef  TPious_SetPluginDelay
 *  \brief    Sets plugin delay in samples for the current batch.
 *
 *  \warning  Must be called during unit/module init or render method.
 */
typedef void (*TPious_SetPluginDelay)(struct Pious_Scope *scope, float plugin_delay_samples);

/*! \typedef  TPious_SetUnitSpec
 *  \brief    Sets spec for currently executing unit/module during initialization.
 */
typedef void (*TPious_SetUnitSpec)(struct Pious_Scope *scope, struct Pious_UnitSpec *spec);

/*! \typedef  TPious_AddUnitIoSpec
 *  \brief    Adds i/o spec for currently executing unit/module during initialization.
 */
typedef void (*TPious_AddUnitIoSpec)(struct Pious_Scope *scope, struct Pious_UnitIoSpec *spec);

/*! \struct Pious_Scope
 *  \brief  Provides a scoped API for units and modules to call during initialization and render.
 */
struct Pious_Scope {
  Pious_U8 private_data[16];
  /*! \sa TPious_GetSampleRate */
  TPious_GetSampleRate GetSampleRate;
  /*! \sa TPious_SetPluginDelay */
  TPious_SetPluginDelay SetPluginDelay;
  /*! \sa TPious_SetUnitSpec */
  TPious_SetUnitSpec SetUnitSpec;
  /*! \sa TPious_AddUnitIoSpec */
  TPious_AddUnitIoSpec AddUnitIoSpec;
};

#endif /*PIOUS_PIOUS_H*/

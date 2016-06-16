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
/*! \file   pious_unit.h
 *  \brief  Declares API for Pious Units.
 *
 *  A Pious Unit processes incoming data and produces an output without the
 *  need for an interface.
 */
#ifndef PIOUS_PIOUS_UNIT_H
#define PIOUS_PIOUS_UNIT_H

#include "pious_types.h"

/***
 ***/


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

struct Pious_HoldSignalEvent {
  Pious_S32 offset;
  Pious_F32 old_value;
  Pious_F32 new_value;
};

struct Pious_UnitIoRef {
  const float* (*GetSignalInPtr)();
  float* (*GetSignalOutPtr)();
  void (*SetSignalOutEmpty)(bool is_empty);
  const Pious_DataPacket* (*GetDataIn)();
  void (*WriteData)(const Pious_DataPacket *data);
};

struct Pious_UnitScope {
  struct Pious_UnitIoRef* (*GetUnitIoRef)(struct Pious_UnitScope *scope, const char *id);
  struct Pious_UnitIoRef* (*GetUnitIoRef_i)(struct Pious_UnitScope *scope, Pious_S32 iid);
  float (*GetSampleRate)(struct Pious_UnitScope *scope);
  void (*SetPluginDelay)(struct Pious_UnitScope *scope, float plugin_delay_samples);
  void (*SetUnitSpec)(struct Pious_UnitScope *scope, struct Pious_UnitSpec *spec);
  void (*AddUnitIoSpec)(struct Pious_UnitScope *scope, struct Pious_UnitIoSpec *spec);
};


/** Methods PiousUnits will have to implement **/

/*! \typedef  Pious_UnitPluginSpec
 *  \brief    Echoes plugin spec to the scope.
 */
typedef void (*Pious_UnitPluginSpec)(struct Pious_UnitScope *scope);
/*! \typedef  Pious_UnitPluginUnit
 *  \brief    Initializes plugin and returns new data pointer.
 *
 *  Initializes the plugin and returns a new pointer to its data to be used by
 *  the Pious_UnitPluginRender method.
 */
typedef void* (*Pious_UnitPluginInit)(struct Pious_UnitScope *scope);
/*! \typedef  Pious_UnitPluginRender
 *  \brief    Renders output
 */
typedef void (*Pious_UnitPluginRender)(struct Pious_UnitScope *scope, void *data, Pious_S32 frames);

#endif /*PIOUS_PIOUS_UNIT_H*/

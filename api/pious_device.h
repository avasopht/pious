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
/*! \file   pious_device.h
 *  \brief  Declares API for Pious Devices.
 *
 *  There are two types of devices, units and modules.
 *
 *  A Pious Unit processes incoming data and produces an output without the
 *  need for a graphical interface (unlike Pious Modules).
 *
 *  Pious units have input and output ports that can transmit audio, sample and hold
 *  signals (aka Control Voltage) and raw data.
 *
 *  Pious Modules have the same functionality of Pious Units but also have an
 *  optional user interface.
 */

#ifndef PIOUS_PIOUS_DEVICE_H
#define PIOUS_PIOUS_DEVICE_H

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Forward declaration */

struct Pious_Scope;
struct Pious_UnitSpec;
struct Pious_UnitIoSpec;


/******************************************************************************
 * I/o data types */

/*!
 *  \brief    Stores a 'hold signal' event.
 */
struct Pious_HoldSignalEvent {
  /*! Batch offset in samples */
  int32_t offset;
  float old_value;
  float new_value;
};

struct Pious_Handle {
  uint8_t private_data[16];
};

/*!
 *  \brief  Holds a variable length data packet.
 *
 *  Holds a variable length data packet sent and received by Pious units and
 *  modules.
 */
struct Pious_DataPacket {
  /*!
   *  \brief  Batch offset in samples.
   */
  int32_t offset;
  /*!
   *  \brief  Length of data array in bytes.
   */
  uint32_t data_length;
  /*!
   *  \brief  Variable length data.
   */
  uint8_t data[4];
};


/******************************************************************************
 * Pious Unit */

/* Methods PiousUnits will have to implement **/

/*!
 *  \brief    Initializes plugin and returns new data pointer.
 *
 *  Initializes the plugin and returns a new pointer to its data to be used by
 *  the Pious_UnitPluginRender method.
 */
typedef void* (*TPious_UnitPluginInit)(struct Pious_UnitScope *scope);
/*!
 *  \brief    Renders output
 */
typedef void (*TPious_UnitPluginRender)(struct Pious_UnitScope *scope, void *data, uint32_t frames);

struct Pious_UnitPlugin {
  TPious_UnitPluginInit Init;
  TPious_UnitPluginRender Render;
};

/*!
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


/******************************************************************************
 * Pious Scope methods */


/*!
 *  \brief    Returns samplerate of scope.
 */
typedef float (*TPious_GetSampleRate)(struct Pious_Scope *scope);

/*!
 *  \brief    Sets plugin delay in samples for the current batch.
 *
 *  \warning  Must be called during unit/module init or render method.
 */
typedef void (*TPious_SetPluginDelay)(struct Pious_Scope *scope, float plugin_delay_samples);

/*!
 *  \brief  Reads signal for given signal handle into dest. Returns number of samples read.
 */
typedef uint32_t (*TPious_ReadSignal)(struct Pious_Scope *scope, Pious_Handle signal_handle,
                                      float *dest, uint32_t max_samples);

/*! \brief  Reads signal hold events, returning number of events read. */
typedef uint32_t (*TPious_ReadSignalEvents)(struct Pious_Scope *scope, Pious_Handle handle,
                                            Pious_HoldSignalEvent *dest, uint32_t max_event_count);

/*! \brief Writes signal hold events. */
typedef bool (*TPious_WriteSignalEvents)(struct Pious_Scope *scope, Pious_Handle handle,
                                         const Pious_HoldSignalEvent *events, uint32_t event_count);

/*!
 *  \brief  Writes signal to buffer indicated by handle.
 */
typedef bool (*TPious_WriteSignal)(struct Pious_Scope *scope, Pious_Handle signal_handle,
                                   const float *source, uint32_t sample_count);

/*! \brief  Returns handle given by object uri */
typedef struct Pious_Handle (*TPious_GetHandle)(struct Pious_Scope *scope, const char *object_uri);

/*! \brief  Returns whether handle is valid. */
typedef bool (*TPious_IsValidHandle)(struct Pious_Scope *scope, Pious_Handle handle);

/*!
 *  \brief  Provides a scoped API for units and modules to call during initialization and render.
 */
struct Pious_Scope {
  int8_t private_data[16];
  /*! \sa TPious_GetSampleRate */
  TPious_GetSampleRate GetSampleRate;
  /*! \sa TPious_SetPluginDelay */
  TPious_SetPluginDelay SetPluginDelay;
  /*! \sa TPious_GetHandle */
  TPious_GetHandle GetHandle;
  /*! \sa TPious_IsValidHandle */
  TPious_IsValidHandle IsValidHandle;
  /*! \sa TPious_ReadSignal */
  TPious_ReadSignal ReadSignal;
  /*! \sa TPious_ReadSignalEvents */
  TPious_ReadSignalEvents ReadSignalEvents;
  /*! \sa TPious_WriteSignal */
  TPious_WriteSignal WriteSignal;
  /*! \sa TPious_WriteSignalEvents */
  TPious_WriteSignalEvents WriteSignalEvents;
};

#ifdef __cplusplus
}
#endif

#endif /*PIOUS_PIOUS_DEVICE_H*/

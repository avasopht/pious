/*
 * Created by The Pious Authors on 22/04/2016.
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

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The pious struct manages objects, connections and DSP processing.
 *
 * Pious is a state based system much like OpenGL
 */
struct pious;

/*
 * About module and composite modules:
 *
 *  GLOBAL_DEVICES = [
 *    MODULE: {
 *      ID,
 *      port_type*: [   // e.g. audio_inputs
 *        PORT_ID       // e.g. "audio_in"
 *      ],
 *      DEVICES: [
 *        MODULE_ID,      // ID of the module
 *        REF_ID,       // how this device will be referenced in the connections section
 *        ALIASES: [
 *          [original, alias] // e.g. port named "out" renamed to "gr_out"
 *        ]
 *      ],
 *      CONNECTIONS: [
 *        {
 *          FIRST: [ "path", "to_port" ], // e.g. ["gain_device", "out"]
 *          SECOND: [ "path/to_port" ]    // e.g. ["rc_device/audio_in"]
 *        }
 *      ]
 *    }
 *  ]
 */

enum pious_io_type {
  PIOUS_IO_TYPE_NONE,
  PIOUS_IO_TYPE_AUDIO_IN,
  PIOUS_IO_TYPE_AUDIO_OUT,
  PIOUS_IO_TYPE_MIDI_IN,
  PIOUS_IO_TYPE_MIDI_OUT,
  PIOUS_IO_TYPE_CONTROL_IN,
  PIOUS_IO_TYPE_CONTROL_OUT
};


/* Creates and initializes a pious database. */
struct pious *create_pious();
/* Destroys pious database and all objects. */
void destroy_pious(struct pious *p);
/* Creates a module and enters MODULE state. */
void pious_begin_module(struct pious *p, const char *sid, int iid);
void pious_begin_module_s(struct pious *p, const char *sid);
void pious_begin_module_i(struct pious *p, int iid);
/* Ends MODULE state. */
void pious_end_module(struct pious *p);
struct pious_module *pious_find_module(struct pious *p, const char *sid, int iid);
struct pious_module *pious_find_module_s(struct pious *p, const char *sid);
struct pious_module *pious_find_module_i(struct pious *p, int iid);
/*
 * Registers a DSP processor (unnecessary for composite modules).
 */
void pious_register_module_dsp(struct pious *p, const struct pious_dsp *dsp);
/* Adds an IO to the module (must be in MODULE state). */
void pious_add_io(struct pious *p, enum pious_io_type io_type, const char *sid, int iid);
/*
 * Adds a child module to a composite module.
 *
 * Begin state: MODULE
 * Return state: MODULE_REF
 */
void pious_begin_module_ref(struct pious *p, const char *sid, int iid);
void pious_begin_module_ref_s(struct pious *p, const char *sid);
void pious_begin_module_ref_i(struct pious *p, int iid);
/*
 * Ends module ref creation.
 *
 * Begin state: MODULE_REF
 * Return state: MODULE
 */
void pious_end_module_ref(struct pious *p);
/*
 * Begins creation of an alias.
 * 
 * Begin state: MODULE_REF
 * End state: MODULE_REF_ALIAS
 */
void pious_begin_alias(struct pious *p);
/*
 * Sets the original port id that can be referenced by an alias.
 *
 *
 * Begin state: MODULE_REF_ALIAS
 */
void pious_set_original(struct pious *p, const char *original_sid, int original_iid);
void pious_set_original_s(struct pious *p, const char *original_sid);
void pious_set_original_i(struct pious *p, int original_iid);
/*
 * Sets the alias id to reference a named port of a module.
 *
 * Begin state: MODULE_REF_ALIAS
 */
void pious_set_alias(struct pious *p, const char *alias_sid, int alias_iid);
void pious_set_alias_s(struct pious *p, const char *alias_sid);
void pious_set_alias_i(struct pious *p, int alias_iid);
void pious_end_alias(struct pious *p);
/*
 * Begins creation of a module connection within a composite module.
 *
 * Begin state: MODULE
 * Return state: MODULE_CONNECTION
 */
void pious_begin_connection(struct pious *p);
/*
 * Ends creation of a module connection
 *
 * Begin state: MODULE_CONNECTION
 * Return state: MODULE
 */
void pious_end_connection(struct pious *p);
/*
 * Sets the first connection of a composite module. Alias names take priority.
 *
 * Begin state: MODULE_CONNECTION
 */
void pious_set_first_connection(struct pious *p, const struct pious_path *path);
/*
 * Sets the second connection of composite module. Alias names take priority.
 *
 * Begin state: MODULE_CONNECTION
 */
void pious_set_second_connection(struct pious *p, const struct pious_path *path);

/*
 * Constructs modules based on information provided. This can be called as often
 * as desired. Modules that have 
 */
void pious_construct_modules(struct pious *p);

struct pious_instance *pious_create_instance_s(struct pious *p, const char *sid);
struct pious_instance *pious_create_instance_i(struct pious *p, const char *iid);
void pious_destroy_instance(struct pious *p, struct pious_instance *instance);

/** Returns PIOUS_TRUE if ctx is in a ROOT state. */
int pious_is_in_root_state(const struct pious *p);
/** Returns PIOUS_TRUE if ctx is in MODULE state. */
int pious_is_in_module_state(const struct pious *p);
/** Returns PIOUS_TRUE if ctx is in Unit Device state. */
int pious_is_in_module_ref_state(const struct pious *p);
/** Returns PIOUS_TRUE if ctx is in Unit Connection state. */
int pious_is_in_module_connection_state(const struct pious *p);
/** Returns PIOUS_TRUE if ctx is in Unit Connection state. */
int pious_is_in_module_alias_state(const struct pious *p);



#ifdef __cplusplus
}
#endif

#endif /*PIOUS_PIOUS_H*/

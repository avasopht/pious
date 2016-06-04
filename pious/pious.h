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

#include <stddef.h>

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
 * The pious_browser manages browsing state so that you can examine what
 * devices are loaded, what their port names and types are, etc.
 */
struct pious_browser;

/*
 * About module and composite modules:
 *
 *  GLOBAL_MODULES = [
 *    MODULE: {
 *      ID,
 *      port_type*: [   // e.g. audio_inputs
 *        PORT_ID       // e.g. "audio_in"
 *      ],
 *      MODULE_REFS: [     // Composite modules
 *        MODULE_REF: {
 *          SECTION,        // monophonic or polyphonic section (optional, assumed monophonic).
 *          MODULE_ID,      // ID of the module
 *          REF_ID,         // ID this module will be referenced by in the connections section.
 *          ALIASES: [
 *            [original, alias] // e.g. port named "out" renamed to "gr_out"
 *          ]
 *        }
 *      ],
 *      CONNECTIONS: [
 *        {
 *          FIRST: ["path", "to_port"], // e.g. ["gain_module", "out"]
 *          SECOND: ["path/to_port"]    // e.g. ["rc_module/audio_in"]
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



enum pious_bool {
  PIOUS_FALSE,
  PIOUS_TRUE
};

/* Creates and initializes a pious database. */
struct pious *create_pious();
/* Destroys pious database and all objects. */
void destroy_pious(struct pious *p);

/****
 * Query and navigation methods.
 */


void pious_browser_init(struct pious_browser *p, struct pious *context);

/* Returns number of constructed modules. */
int pious_browser_get_module_count(struct pious_browser *p);
/* Enters n'th module, returning PIOUS_TRUE on success */
enum pious_bool pious_browser_enter_module_at(struct pious_browser *p, int index);
/* Exits current module (thus returning to the root node). */
void pious_browser_exit_module(struct pious_browser *p);
/* Returns name of current module into `out_name` or null. */
const char* pious_browser_read_module_name(struct pious_browser *p, char *out_name, size_t buf_size);
/* Returns whether current module is a plugin. */
enum pious_bool pious_browser_is_module_plugin(struct pious_browser *p);
/* Reads name of plugin of module (if any) into `out_name`. Returns actual size of plugin name. */
size_t pious_browser_read_plugin_name(struct pious_browser *p, char *out_name, size_t buf_size);
/* Returns current module's number of io ports for the current module (or -1 on error). */
int pious_browser_get_io_count(struct pious_browser *p);
/* Returns current module's number of io ports of a particular type (or -1 on error). */
int pious_browser_get_io_type_count(struct pious_browser *p, enum pious_io_type io_type);
/* Enters module's nth io port. */
void pious_browser_enter_io_at(struct pious_browser *p, char *out_path, size_t buf_size, int index);
/* Enters module's nth io port. */
void pious_browser_enter_io_type_at(struct pious_browser *p, char *path_out, int index, enum pious_io_type io_type);

/****
 * Module building methods.
 */

/* Creates a module and enters MODULE state. */
void pious_begin_module(struct pious *p, const char *id);
void pious_begin_module_si(struct pious *p, const char *sid, int iid);
void pious_begin_module_i(struct pious *p, int iid);
/* Ends MODULE state. */
void pious_end_module(struct pious *p);
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
void pious_begin_module_ref(struct pious *p, const char *sid);
void pious_begin_module_ref_si(struct pious *p, const char *sid, int iid);
void pious_begin_module_ref_i(struct pious *p, int iid);
void pious_begin_module_ref_p(struct pious *p, const char *plugin_uuid);
/*
 * Ends module ref creation.
 *
 * Begin state: MODULE_REF
 * Return state: MODULE
 */
void pious_end_module_ref(struct pious *p);
/*
 * Sets whether the reference module is polyphonic.
 */
void pious_set_ref_polyphonic(struct pious *p, enum pious_bool is_polyphonic);
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
 * Begin state: MODULE_REF_ALIAS
 */
void pious_set_original(struct pious *p, const char *original_id);
/* As pious_set_original but with explicit string and integer id. */
void pious_set_original_si(struct pious *p, const char *original_sid, int original_iid);
/* As pious_set_original, but sets only the integer id. */
void pious_set_original_i(struct pious *p, int original_iid);
/*
 * Sets the alias id to reference a named port of a module.
 *
 * Begin state: MODULE_REF_ALIAS
 */
void pious_set_alias(struct pious *p, const char *alias_id);
/* Same as pious_set_alias, but providing explicit string and integer id */
void pious_set_alias_si(struct pious *p, const char *alias_sid, int alias_iid);
/* Same as pious_set_alias, but providing explicit integer id */
void pious_set_alias_i(struct pious *p, int alias_iid);
/*
 * Ends creation of alias.
 *
 * Begin state: MODULE_REF_ALIAS
 * Return state: MODULE_REF
 */
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
/*
 * Constructs module with a given id.
 */
void pious_construct_module(struct pious *p, const char *id);
/* Same as pious_construct_module but providing explicit string and integer id. */
void pious_construct_module_si(struct pious *p, const char *sid, int iid);
/* Same as pious_construct_module but providing explicit integer id. */
void pious_construct_module_i(struct pious *p, int iid);

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

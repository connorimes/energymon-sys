/**
 * API for reading energy values. Different platforms may need different
 * implementations.  For example, X86-based systems may be able to share an
 * implementation that reads from the MSR, while other systems may have to read
 * from power sensors and convert power readings to energy.
 *
 * Pointers to implementations of the typedef'd functions below are included
 * in the energymon struct for encapsulation.
 *
 * Implementations should set (or preserve) errno on failure. Additionally,
 * they may preemptively print error messages if too much context would be lost
 * otherwise.
 *
 * @author Connor Imes
 * @date 2014-06-30
 */
#ifndef _ENERGYMON_H_
#define _ENERGYMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stddef.h>

typedef struct energymon energymon;

/**
 * Open required file(s), start necessary background tasks, etc.
 * Typically allocates the state field of the energymon struct.
 *
 * @param pointer to an energymon
 * @return 0 on success, failure code otherwise
 */
typedef int (*energymon_init) (energymon*);

/**
 * Get the total energy in microjoules.
 *
 * @param pointer to an energymon
 * @return energy (in uJ)
 */
typedef uint64_t (*energymon_read_total) (const energymon*);

/**
 * Stop background tasks, close open file(s), free memory allocations, etc.
 * Typically frees the state field of the energymon struct.
 *
 * @param pointer to an energymon
 * @return 0 on success, failure code otherwise
 */
typedef int (*energymon_finish) (energymon*);

/**
 * Get a human-readable description of the energy monitoring source.
 * Implementations should ensure that the buffer is null-terminated.
 *
 * @param pointer to a buffer
 * @param the maximum number of bytes to write
 * @return pointer to the same buffer, or NULL on failure
 */
typedef char* (*energymon_get_source) (char* buffer, size_t n);

/**
 * Get the refresh interval in microseconds of the underlying sensor(s).
 * This value should be greater than 0 except in error cases.
 * If there is no minimum interval, return 1.
 *
 * @param pointer to an energymon
 * @return the refresh interval, or 0 on error
 */
typedef uint64_t (*energymon_get_interval) (const energymon*);

/**
 * A structure to encapsulate a complete implementation. The first five fields
 * are pointers to required functions. The state field is managed by the
 * implementation.
 */
struct energymon {
  energymon_init finit;
  energymon_read_total fread;
  energymon_finish ffinish;
  energymon_get_source fsource;
  energymon_get_interval finterval;
  void* state;
};

#ifdef __cplusplus
}
#endif

#endif

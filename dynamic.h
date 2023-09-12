/**
 * @file dynamic.h
 * @author Deniz Deli, Christoph Binner, Christian Kastner <br>
 * <br>
 * @brief Audio Object for a simple audio compressor<br>
 * <br>
 * dynamic allows for adjusting the dynamic<br>
 * of any incoming mono audio signal. <br>
 * <br>
 */

#ifndef dynamic_h
#define dynamic_h

#include <stdio.h>
#include <stdlib.h>
#include "m_pd.h"

typedef float INPUTVECTOR;
typedef float OUTPUTVECTOR;

/**
 * @struct dynamic
 * @brief A structure for a audio compressor object <br>
 * @var threshold The parameter value for adjusting the <br>
 * threshold
 * @var ratio The parameter value for adjusting the <br>
 * ratio
 * @var attack The parameter value for adjusting the <br>
 * attack time
 * @var release The parameter value for adjusting the <br>
 * release time
 * @var samplerate The parameter value for adjusting the <br>
 * samplerate
 */

typedef struct dynamic
{
        float threshold; /**< parameter for adjusting the threshold of the compressor */
	float ratio; /**< parameter for adjusting the ratio of the compression */
	float attack; /**< parameter for adjusting the attack time of the compressor */
	float release; /**< parameter for adjusting the release time of the compressor */
	float samplerate;
} dynamic;

/**
 * @related dynamic
 * @brief Creates a new brickwall object<br>
 * The function creates a new dynamic object <br>
 * @return a pointer to the newly created dynamic object <br>
 */

dynamic *dynamic_new();

/**
 * @related dynamic
 * @brief Frees a dynamic object<br>
 * @param x My brickwall object to delete.<br>
 * The function frees the allocated memory<br>
 * of a gain object
 */

void dynamic_free(dynamic *x);

/**
 * @related dynamic
 * @brief Sets the threshold parameter <br>
 * @param x My dynamic object <br>
 * @param threshold The threshold value <br>
 * The function sets the threshold parameter of <br>
 * the dynamic class
 */

void dynamic_setthreshold(dynamic *x, float threshold);

/**
 * @related dynamic
 * @brief Sets the ratio parameter <br>
 * @param x My dynamic object <br>
 * @param ratio The ratio value <br>
 * The function sets the ratio parameter of <br>
 * the dynamic class
 */

void dynamic_setRatio(dynamic *x, float ratio);

/**
 * @related dynamic
 * @brief Sets the attack parameter <br>
 * @param x My dynamic object <br>
 * @param attack The attack value <br>
 * The function sets the attack parameter of <br>
 * the dynamic class
 * @note The attack time value is in samples
 * @warning Values below 1000 may cause dropouts
 */

void dynamic_setAttack(dynamic *x, float attack);

/**
 * @related dynamic
 * @brief Sets the release parameter <br>
 * @param x My dynamic object <br>
 * @param release The release time value <br>
 * The function sets the release time parameter of <br>
 * the dynamic class
 * @note The release time value is in samples
 * @warning Values below 1000 may cause dropouts
 */

void dynamic_setRelease(dynamic *x, float release);

void dynamic_perform(dynamic *x, INPUTVECTOR *in, OUTPUTVECTOR *out, int vectorSize);

/**
 * @related dynamic
 * @brief Performs the level adjustment in realtime <br>
 * @param x My dynamic object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vectorSize The vectorSize <br>
 * The function dynamic_compress performs the gain adjustment of <br>
 * the incoming signal and copies the result to the output vector <br>
 */

void dynamic_compress(dynamic *x, INPUTVECTOR *in, OUTPUTVECTOR *out, int vectorSize);

#endif /* dynamic_h */

#include "dynamic.h"
#include <math.h>

float curr_atten_fac = 1.0;
float *ptr_curr_atten = &curr_atten_fac;

float attack_active = 0;
float *ptr_attack_active = &attack_active;

dynamic *dynamic_new()
{
	dynamic *x = (dynamic *)malloc(sizeof(dynamic));
	x->threshold = 1.0;
	x->ratio = 1.0;
	x->attack = 10.0;
	x->release = 100.0;
	//x->makeUpLevel = 0.0;
	//x->clippingLevel = 1.0;
	x->samplerate = 44100;
    return x;
}

void dynamic_free(dynamic *x)
{
    free(x);
}

void dynamic_setthreshold(dynamic *x, float threshold)
{
	if(threshold < 0)
		threshold = 0.01;
	x->threshold = threshold;
}

void dynamic_setRatio(dynamic *x, float ratio)
{
	if(ratio < 1)
		ratio = 1;
	x->ratio = ratio;
}

void dynamic_setAttack(dynamic *x, float attack)
{
	if(attack < 1)
		attack = 1;
	x->attack = attack;
}

void dynamic_setRelease(dynamic *x, float release)
{
	if(release < 1)
		release = 1;
	x->release = release;
}

void dynamic_compress(dynamic *x, INPUTVECTOR *in, OUTPUTVECTOR *out, int vectorSize)
{
	//maximum attenuation calculated from threshold and ratio
	float atten_max = x->threshold+(1-x->threshold)*(1/x->ratio);

	//increments for transition from uncompressed to compressed signal,
	//logarithmic change over attack/release time
	float attack_delta = pow(atten_max,1/x->attack);
	float release_delta = pow(atten_max,1/x->release);

	for (int i = 0; i < vectorSize; i++)
	{
		//DSP
		*out = *in * *ptr_curr_atten;

		//attenuation factor manipulation
		if(*ptr_attack_active)
		{
			//gradually transition to compressed signal
			*ptr_curr_atten *= attack_delta;

			if(*ptr_curr_atten < atten_max)
			{
				//disable attack flag once max compression is reached
				*ptr_attack_active = 0;
				//safeguard
				*ptr_curr_atten = atten_max;
			}
		}
		else
		{
			//trigger compressor, negative peaks are not considered
			if(*in>x->threshold)
			{
				*ptr_attack_active = 1;
			}
			else
			{

				//release attenuation when below threshold
				if(*ptr_curr_atten < 1)
					*ptr_curr_atten /= release_delta;

				//safeguard
				if(*ptr_curr_atten>1)
					*ptr_curr_atten = 1;
			}
		}
		in++;
		out++;

	}
}

void dynamic_perform(dynamic *x, INPUTVECTOR *in, OUTPUTVECTOR *out, int vectorSize)
{
	dynamic_compress(x, in, out, vectorSize);
}

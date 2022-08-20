#include "filters.h"
#include "writer.h"

#define NEUTRAL_THRESHOLD 64

using namespace Filters;

uint8_t Filters::fast (struct HeadlessBitmap* _Data, uint32_t _X, uint32_t _Y, int32_t* _Seed) {

	// moved to externally implemented method reduce number of stack allocations required
	// must be implemented by source subroutine
	// approximated circle
	//uint32_t _Seed[] = { -3, -3, -3, -2, -1, 0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2 };
	
	
	// define central point, sample control
	// unshifted (P)ixel (C)o(L)our bits
	// no need to mask p_cl as the masking comes automatically with shifting and isolation for p_gs
	uint32_t p_cl = *(uint32_t*)(&_Data->data[_Y][_X * 3]);


	// shifted total (P)ixel (G)rey(S)cale integer
	int32_t p_gs = (p_cl & 0xFF) + ((p_cl & 0xFF00) >> 8) + ((p_cl & 0xFF0000) >> 16);

	
	/*if (_X > 700)*/ //printf("%u\n", p_cl);
	uint16_t l_flag = 0;
	uint16_t h_flag = 0;


	// initial checks, 4 cardinal directions
	// for a contiguous pixel of high/lows, at least 3 cardinal directions must be either high or low for this to be true
	for (uint32_t i = 0; i < 16; i += 4) {
		// target pixel, unshifted, colour, in rasterised circular pattern

		int32_t x = (_X + _Seed[i]);
		int32_t y = _Y + _Seed[(i + 4) % 16];


		int32_t t_gs;
		// if range exceeds image limits
		if (x < 0 || x >= _Data->x || y < 0 || y >= _Data->y) {
			t_gs = p_gs;

		}
		else {
			
			// sum up greyscale representation of target pixel
			uint32_t t_cl = *((uint32_t*)&_Data->data[y][x * _Data->pixel_width]);
			
			t_gs = (t_cl & 0xFF) + ((t_cl & 0xFF00) >> 8) + ((t_cl & 0xFF0000) >> 16);
		}



		if (t_gs - p_gs > NEUTRAL_THRESHOLD) {
			h_flag++;
			
		}// t_gs is brighter than p_gs, significantly, add to high flag

		else if (p_gs - t_gs > NEUTRAL_THRESHOLD) l_flag++; // p_gs is brighter than t_gs, significantly
	}

	/*if (h_flag <= 3) { // if possibly contiguous pattern of brighter pixels exist

		// reset for use as bit flags
		h_flag = 0;

		for (uint32_t i = 0; i < 16; i++) {



			uint32_t x = _X * 3 + _Seed[i];
			uint32_t y = _Y + _Seed[(i + 4) % 16];

			int32_t t_gs;
			// if range exceeds image limits
			if (x < 0 || x > _Data->x || y < 0 || y >= _Data->y) {
				t_gs = p_gs;
			}
			else {
				uint32_t t_cl = *((uint32_t*)&_Data->data[y][x]) & 0x00FFFFFF;
				t_gs = (t_cl & 0xFF) + (t_cl & 0xFF00 >> 8) + (t_cl & 0xFF0000 >> 16);
			}

			// t_gs is brighter than p_gs (target brighter), significantly, add to high flag
			if (t_gs - p_gs > NEUTRAL_THRESHOLD) h_flag |= 0x1 << i;
		}
	}

	else if (l_flag <= 3) { // if possibly contiguous pattern of darker pixels exist

		// reset for use as bit flags
		l_flag = 0;

		for (uint32_t i = 0; i < 16; i++) {


			uint32_t x = _X * 3 + _Seed[i];
			uint32_t y = _Y + _Seed[(i + 4) % 16];

			int32_t t_gs;
			// if range exceeds image limits
			if (x < 0 || x > _Data->x || y < 0 || y >= _Data->y) {
				t_gs = p_gs;
			}
			else {
				uint32_t t_cl = *((uint32_t*)&_Data->data[y][x]) & 0x00FFFFFF;
				t_gs = (t_cl & 0xFF) + (t_cl & 0xFF00 >> 8) + (t_cl & 0xFF0000 >> 16);
			}

			// p_gs is brighter than t_gs (target darker), significantly, add to high flag
			if (p_gs - t_gs > NEUTRAL_THRESHOLD) l_flag |= 0x1 << i;

		}
	}*/

	// if neither flag has been triggered, which means this definitely does not have >=12 contiguous extrema
	//else return (0);
	if (l_flag < 3 && h_flag < 3) return (0);

	// no finer implementation so far, assumed finer details will be blurred out by preprocessing
	// lazy approach susceptible to missing finer feature rotations
	return (1);


}
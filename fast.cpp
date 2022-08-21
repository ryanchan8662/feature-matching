#include "filters.h"
#include "writer.h"

using namespace Filters;

// _Accuracy: precision of edge detection - 0 = fast FAST, approximation of 270deg corners, some may be missed
// 1 = slow FAST, exact calculation of corners
uint8_t Filters::fast (struct HeadlessBitmap* _Data, uint32_t _X, uint32_t _Y, int32_t* _Seed, int8_t _Accuracy) {

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

	// neutral threshold: central pixel intensity / 4 for proportional intensities
	int32_t n_th = (p_gs >> 1) + 32;

	
	uint16_t l_flag = 0;
	uint16_t h_flag = 0;

	// slow FAST approach ~~~~~~~~~~~~~~~~~~~~~~~~
	if (_Accuracy) {
		// slow FAST checks, all 16 "circle" pixels
		for (uint32_t i = 0; i < 16; i++) {
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


			// t_gs is brighter than p_gs (BRIGHTER TARGET), significantly, add to high flag
			if (t_gs - p_gs > n_th) h_flag |= 0x1 << i;

			// p_gs is brighter than t_gs (DARKER TARGET), significantly
			else if (p_gs - t_gs > n_th) l_flag |= 0x1 << i;
		}

		// check for 12 contiguous pixels

		// perform preliminary checks for blank neutral areas, should speed up analysis for larger, empty areas
		if ((h_flag | l_flag) == 0) return (0);

		else {
			uint8_t h_cont = ~0x0;
			uint8_t l_cont = ~0x0;

			// sum up continguouity
			for (uint8_t i = 0; i < 12; i++) {

				// if the flags are rotated 12 times, totaled using AND bitwise operations, and the result >0, there are at least 12 continguous bits

				/* EXAMPLE:
				1110 0001 1111 1111
				1111 0000 1111 1111
				1111 1000 0111 1111
				1111 1100 0011 1111
				1111 1110 0001 1111
				1111 1111 0000 1111
				1111 1111 1000 0111
				1111 1111 1100 0011
				1111 1111 1110 0001
				1111 1111 1111 0000
				0111 1111 1111 1000
				0011 1111 1111 1100
				-------------------
				0010 0000 0000 0000
				*/

				// rotation: (x << n) | (x >> (16 - n))
				for (uint8_t j = 0; j < 12; j++) {

					h_cont &= ((h_flag << 16 - j) & 0xFFFF) | h_flag >> j;
					l_cont &= ((l_flag << 16 - j) & 0xFFFF) | l_flag >> j;

				}
				//printf("%x, %x, %x, %x\n", h_cont, l_cont, h_flag, l_flag);
				
			}

			// if neither high or lows has a continuous string of 12 "on" bits, invalid
			if ((h_cont | l_cont) == 0) return (0);
		}
	}

	// fast FAST approach ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	else {
		// fast FAST checks, 4 cardinal directions
		// for a contiguous pixel of high/lows, at least 3 cardinal directions must be either high or low for this to be true
		for (uint32_t i = 0; i < 16; i += 4) {
			// target pixel, unshifted, colour, in rasterised circular pattern

			int32_t x = (_X + _Seed[i]);
			int32_t y = _Y + _Seed[(i + 4) % 16];


			int32_t t_gs;
			// if range exceeds image limits
			if (x < 0 || x >= _Data->x || y < 0 || y >= _Data->y) t_gs = p_gs;

			else {

				// sum up greyscale representation of target pixel
				uint32_t t_cl = *((uint32_t*)&_Data->data[y][x * _Data->pixel_width]);

				t_gs = (t_cl & 0xFF) + ((t_cl & 0xFF00) >> 8) + ((t_cl & 0xFF0000) >> 16);
			}


			if (t_gs - p_gs > n_th) h_flag++;// t_gs is brighter than p_gs, significantly, add to high flag

			else if (p_gs - t_gs > n_th) l_flag++; // p_gs is brighter than t_gs, significantly
		}
		
		// if cardinal accumulators below threshold, not a corner
		if (l_flag < 3 && h_flag < 3) return (0);
	}

	// if negative triggers have been skipped, only logical outcome is corner
	return (1);
	

	// no finer implementation so far, assumed finer details will be blurred out by preprocessing
	// lazy approach susceptible to missing finer feature rotations
	


}
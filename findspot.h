#ifndef FINDSPOT_H__
#define FINDSPOT_H__

int integrate(int i0, int j0, int i1, int j1, unsigned char* img, int w);

float findspot(unsigned char* img, 
		int w, 
		int h, 
		int winW, 
		int winH, 
		int& max_i,
		int& max_j)
{
	float background;
	float average;
	float max_corrected = 0.0;

	max_i = -1;
	max_j = -1;
	
	for(int	i=0; i<h-winH; ++i) {
		// process initial window
		int back_tmp, avg_tmp;
		int left_col;
		int right_col;
		int j = 0;
		
		// left column
		left_col = back_tmp = integrate(i, j, i+winH, j+1, img, w);
		
		// upper row
		back_tmp += integrate(i, j+1, i+1, j+winW-1, img, w);
		
		// lower row
		back_tmp += integrate(i+winH-1, j+1, i+winH, j+winW-1, img, w);
		
		// right column
		right_col = integrate(i, j+winW-1, i+winH, j+winW, img, w);
		back_tmp += right_col;
		
		background = (float)back_tmp / (2.0*(float)winH + 2.0*(float)(winW-2));
		//cout << "background = " << background << endl;
		
		avg_tmp = integrate(i+1, j+1, i+winH-1, j+winW-1, img, w);
		average = (float)avg_tmp / (float)((winW-2)*(winH-2));
	
		if( average - background > max_corrected ) {
			max_i = i + winH/2;
			max_j = j + winW/2;
			max_corrected = average - background;
		}
	
		// iterate over following steps
		for(j=1; j<w-winW; ++j) {
			int plus_bg = integrate(i, j+winW-1, i+winH, j+winW, img, w);
			int minus_avg = integrate(i, j, i+winH, j+1, img, w);
			plus_bg += minus_avg;
		
			int minus_bg = integrate(i, j-1, i+winH, j, img, w);
			int plus_avg = integrate(i, j+winW-2, i+winH, j+winW-1, img, w);	
			minus_bg += plus_avg;			

			background += (float)plus_bg / (float)(2*winH);
			background -= (float)minus_bg / (float)(2*winH);


			average += (float)plus_avg / (float)(2*winH);
			average -= (float)minus_avg / (float)(2*winH);

			if( average - background > max_corrected ) {
				max_i = i + winH/2;
				max_j = j + winW/2;
				max_corrected = average - background;
			}
		}
	}

	return max_corrected;
}


int integrate(int i0, int j0, int i1, int j1, unsigned char* img, int w)
{
	int rv = 0;
	
	for(int i=i0; i<i1; ++i) {
		for(int j=j0; j<j1; ++j) {
			rv += (int)img[i*w + j];
		}
	}
	
	return rv;
}

#endif

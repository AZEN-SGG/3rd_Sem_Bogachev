#ifndef DATA_H
#define DATA_H

#include <stdio.h>

class data
{
	private:
		int m = 0;
		double a[M] = {};
		static int p;
	public:
		data () = default;
		~data () = default;

		data (char *name);

		int get_m () const { return m; }
		int get_M () const { return (m < M ? m : M); }

		void set_m (int new_m) { m = new_m; }
		const double * get_a () { return a; }

		static int get_p () { return p; }
		static void set_p (int q) { p = q; }

		data (const data &x) = default;
		data& operator= (const data&) = default;

		int operator< (const data& x) const { return m < x.m; }
		int operator> (const data& x) const { return m > x.m; }

		void print (FILE * fp = stdout) const
		{
			int len = get_M (), i;
			fprintf(fp, "%d", m);
			if (len > p) len = p;
			for (i = 0; i < len; ++i)
				fprintf(fpm " %le", a[i]);
			fprintf(fp, "\n");
		}

		int read (FILE *fp = stdin);
		void init (int s, int n, int i);
};

#endif // data

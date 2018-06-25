
// イージング
double InOutQuad(double t, double totaltime, double max, double min)
{
	max -= min;
	t /= totaltime;
	if (t / 2 < 1)
		return max / 2 * t * t + min;
	--t;
	return -max * (t * (t - 2) - 1) + min;
}
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

def vars_plot(in_file, out_img, title):
	df = pd.read_csv(in_file, delimiter=';')
	df = df.sort_values(['PVF '], ascending=False)
	names = df['Var name ']
	files = df['file ']
	lnums = df['line number']
	labels = [names[i] + ", " + files[i] + ", line " + str(lnums[i])
			  for i in range(len(df))]
	y_pos = np.arange(len(labels))
	pvfs = df['PVF ']

	fig, ax = plt.subplots()
	ax.barh(y_pos, pvfs, color='red', ecolor='black')
	ax.set_yticks(y_pos)
	ax.set_yticklabels(labels)
	ax.invert_yaxis()
	ax.set_xlabel('PVF')
	ax.set_title(title)
	plt.tight_layout()
	fig.set_size_inches(6.5, 9)
	plt.savefig(out_img)


if(__name__ == "__main__"):
	if(len(sys.argv) != 4):
		print("Args.: input csv file, output image file, title")
	else:
		vars_plot(sys.argv[1], sys.argv[2], sys.argv[3])

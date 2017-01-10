import matplotlib.pyplot as plt

def createDiagram(times, y_axis):
	#print(times)[:10]
	plt.plot([i[0] for i in times], [i[1] for i in times])
	plt.ylabel(y_axis)
	plt.xlabel('shelf size')
	plt.show()

# Function to display the differences between two strings
def diff(X, Y, m, n, lookup):

	# if the last character of `X` and `Y` matches
	if m > 0 and n > 0 and X[m - 1] == Y[n - 1]:

		diff(X, Y, m - 1, n - 1, lookup)
		print("", X[m - 1], end='')

	# if the current character of `Y` is not present in `X`
	elif n > 0 and (m == 0 or lookup[m][n - 1] >= lookup[m - 1][n]):

		diff(X, Y, m, n - 1, lookup)
		print(" +" + Y[n - 1], end='')

	# if the current character of `X` is not present in `Y`
	elif m > 0 and (n == 0 or lookup[m][n - 1] < lookup[m - 1][n]):

		diff(X, Y, m - 1, n, lookup)
		print(" -" + X[m - 1], end='')
	print()

# Function to fill the lookup table by finding the length of LCS
def LCSLength(X, Y, m, n, lookup):

	# first column of the lookup table will be all 0
	for i in range(m + 1):
		lookup[i][0] = 0

	# first row of the lookup table will be all 0
	for j in range(n + 1):
		lookup[0][j] = 0

	# fill the lookup table in a bottom-up manner
	for i in range(1, m + 1):

		for j in range(1, n + 1):
			# if current character of `X` and `Y` matches
			if X[i - 1] == Y[j - 1]:
				lookup[i][j] = lookup[i - 1][j - 1] + 1
				# otherwise, if the current character of `X` and `Y` don't match
			else:
				lookup[i][j] = max(lookup[i - 1][j], lookup[i][j - 1])


# Implement diff utility in Python
if __name__ == '__main__':

	X = "ABCDFGHJQZ"
	Y = "ABCDEFGIJKRXYZ"
	# `lookup[i][j]` stores the length of LCS of substring `X[0…i-1]` and `Y[0…j-1]`
	lookup = [[0 for x in range(len(Y) + 1)] for y in range(len(X) + 1)]
	# fill lookup table
	LCSLength(X, Y, len(X), len(Y), lookup)
	# find the difference
	diff(X, Y, len(X), len(Y), lookup)

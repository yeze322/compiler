import linecache
fname = "sample.tny"

class scanner(object):
	def __init__(self, fname):
		self.row, self.col = 0, 0
		self.text = linecache.getlines(fname)
		self.token = '/0'
		self.EOF = False

	def getChar(self):
		if self.EOF:
			return
		if self.col >= len(self.text[self.row]):
			self.row += 1
			self.col = 0;
		if self.row >= len(self.text):
			self.token = '\0'
			self.EOF = True
			return

		self.token = self.text[self.row][self.col]
		self.col += 1
		return

	def getToken(self):
		while True:
			self.getChar()
			if self.token in [' ', '\t', '\n']:
				continue
			elif self.token in "1234567890":
				ret = ""
				while self.token in "1234567890":
					ret += self.token
					self.getChar()
				return ("INNUM", int(ret))
			elif self.token.isalpha():
				ret = ""
				while self.token.isalpha() == True:
					ret += self.token
					self.getChar()
				return ("INID", ret)
			elif self.token == ':':
				self.getChar()
				if self.token == '=':
					return ("INASSIGN", ":=")
				else:
					print "Error Happened! in ASSIGN"
			elif self.token in '{':
				ret = ""
				self.getChar()
				while self.token not in '}\0':
					ret += self.token
					self.getChar()
				return ("INCOMMM",ret)
	def parser


tny = scanner(fname)
while not tny.EOF:
	print tny.getToken()
print "end"










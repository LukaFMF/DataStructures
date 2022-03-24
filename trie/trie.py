import time

class trie_node:
	def __init__(self,value=None):
		self.value = value
		self.children = []
		self.IsWord = False # value is true if the sequence of characters represent a word in a trie

	def trie_sort_rec(self,word=''):
		'''we give a list object in which there are all words that are currently in our trie alphabetically ordered.'''
		tab_words = []
		if self.IsWord:
			tab_words.append(word)
		for el in self.children:
			words = el.trie_sort_rec(word + el.value)
			tab_words.extend(words)
		return tab_words


class trie:
	def __init__(self):
		self.root = trie_node()

	def insert(self,word):
		current_node = self.root
		for i in range(len(word)):
			pointer = 0
			isin = False
			key = word[i].lower()
			tab_of_children = current_node.children
			for ind in range(len(tab_of_children)):
				ch = tab_of_children[ind].value
				if key == ch: # branch already exists
					isin = True
					break
				if key < ch: # we insert a key node in the list
					break
				pointer += 1
			if not isin: # key was not in the list 
				 tab_of_children.insert(pointer,trie_node(key))
			current_node = tab_of_children[pointer] # we continue from the right node foreward
		current_node.IsWord = True

	def trie_sort(self):
		return self.root.trie_sort_rec()

	def trie_query(self,word):
		current_node = self.root
		for i in range(len(word)):
			found = False
			inx = 0
			for el in current_node.children:
				if el.value == word[i].lower():
					found = True
					break # we found our path
				inx += 1
			if not found:
				return []
			current_node = current_node.children[inx]   
		return current_node.trie_sort_rec(word)

	def __contains__(self,word):
		current_node = self.root
		for i in range(len(word)):
			found = False
			inx = 0
			for el in current_node.children:
				if el.value == word[i].lower():
					found = True
					break # we found our path
				inx += 1
			if not found:
				return False
			current_node = current_node.children[inx] 
		return current_node.IsWord

	def trie_delete(self,word):

		def trie_del(node,word):

			if len(word) == 0:
				if node.IsWord: # potrdimo, da smo res nasli besedo
					node.IsWord = False

					# vozlisca bomo brisali, le ce beseda ni predpona neke druge besede
					return len(node.children) == 0 
				return False
			else:
				cont = False # ta vrednost pove, ce moramo se naprej brisati vozlisca
				inx = None
				# najdemo vozlisce, ki vodi no naslednjega znaka v besedi
				for i in range(len(node.children)):
					if node.children[i].value == word[0]:
						cont = trie_del(node.children[i],word[1:])
						inx = i
						break

				if cont:
					node.children.pop(inx) # izbrismo vozlisce

					# z brisanjem nadaljujemo, ce trenutno vozlisce ne predstavlja 
					# besede in ni predpona drugih besed
					if node.IsWord or len(node.children) > 0:
						cont = False

				return cont

		# funkcija sicer vrne neko vrednost(True/False), a je ne posredujemo naprej
		trie_del(self.root,word)

	def trie_delete_word(self,word):
		current_node = self.root

		depth = -1
		tab_inx = []
		tab_nodes = []

		# premaknemo se na dano besedo
		for i in range(len(word)):
			found = False
			for ind in range(len(current_node.children)):
				if current_node.children[ind].value == word[i]:
					found = True
					break 
			
			if not found:
				return
			tab_inx.append(ind)
			tab_nodes.append(current_node)
			current_node = current_node.children[ind]
			depth += 1

		current_node.IsWord = False

		if len(current_node.children) != 0:
			return
		
		while depth >= 0:
			inx = tab_inx[depth]
			node = tab_nodes[depth]

			node.children.pop(inx)

			if node.IsWord or len(node.children) != 0:
				return

			depth -= 1


#==================================
# test cases:
#==================================
# with open('TheHungerGamesWords.txt','r') as dat:
#     t = trie()
#     tab = []
#     for el in dat.readlines():
#         beseda = el.strip()
#         t.insert(beseda)
#         tab.append(beseda)
#     a = '9'
#     t1 = time.time()
#     for _ in range(10000):
#         a in t
#     t2 = time.time()
#     mn = set(tab)
#     for _ in range(10000):
#         a in mn
#     t3 = time.time()
#     print(t2-t1)
#     print(t3-t2)
tr = trie()
tab = ['ananas','avto','avtomat','avion','bazen','balon','cesta']
for el in tab:
	tr.insert(el)
print(tr.trie_sort())
tr.trie_delete_word("avto")

tr.trie_delete_word("ananas")
tr.trie_delete_word("avion")
tr.trie_delete_word("bazen")
tr.trie_delete_word("balon")
tr.trie_delete_word("ce")


print(tr.trie_sort())








	



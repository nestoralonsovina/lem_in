#include "../includes/lem_in.h"
#include <stdbool.h>

static int count = 0;

t_trie	*trie_create()
{
	t_trie *p_node;

	p_node = NULL;
	p_node = (t_trie *)malloc(sizeof(t_trie));
	if (p_node)
	{
		p_node->value = '\0';
		p_node->count =0;
		ft_memset(p_node->children, 0, sizeof(p_node->children));
	}
	return (p_node);
}

void	insert_trie(t_trie* root, char* word) {

	t_trie	*p_crawl;
	int		index;
	int		i;

	if (!word || !root)
		return ;
	p_crawl = root;
	count++;
	index=0;
	i =0;
	while( word[i] != '\0')
	{
		index = (int)(word[i]) - (int)'!';
		if(!p_crawl->children[index])
		{
			p_crawl->children[index] = trie_create();
			p_crawl->children[index]->value = word[i];
		}
		p_crawl = p_crawl->children[index];
		i++;
	}
	p_crawl->count = count;
}

int		search_trie(t_trie * root, char* word)
{
	t_trie	*p_crawl;
	int		flag;
	int		i;
	int		index;

	flag = 0;
	p_crawl = root;
	i = 0;
	index = 0;
	if(!word || !root)
		return (0);
	if (*word == '\0')
		return (1);
	while (word[i] != '\0')
	{
		index = (int)(word[i]) - (int)'!';
		if(!p_crawl->children[index])
			break;
		p_crawl = p_crawl->children[index];
		i++;
	}
	if(p_crawl->count != 0 && word[i] == '\0')
		flag = 1;
	return (flag);
}

void trie_free(t_trie* root)
{
	size_t i;

	i = 0;
	if(root)
	{
		while (i < 93)
			trie_free(root->children[i++]);
		free(root);
	}
}

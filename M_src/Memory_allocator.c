/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Memory_allocator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:54:52 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/29 14:54:55 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*Cette fonction crée un nouveau nœud de la structure t_alloc.
Elle alloue dynamiquement de la mémoire pour le nœud .
Si l'allocation de mémoire réussit, elle attribue l'adresse adr passée en 
argument au champ adr du nœud et initialise le champ next à NULL.
Enfin, elle renvoie un pointeur vers le nœud nouvellement créé.*/

t_alloc	*new_node(void *adr)
{
	t_alloc	*node;

	node = malloc(sizeof(t_alloc));
	if (!node)
		return (NULL);
	node->adr = adr;
	node->next = NULL;
	return (node);
}

/*Cette fonction est utilisée pour ajouter un nœud contenant une adresse adr
à une liste chaînée, Si la liste n'est pas vide, la fonction parcourt la liste 
jusqu'à trouver le dernier nœud, puis elle ajoute le nouveau nœud node à la fin
de la liste en mettant à jour le champ next du dernier nœud.*/

t_alloc	**add_adr(t_alloc **g_memory, void *adr)
{
	t_alloc	*node;
	t_alloc	*tmp;

	node = new_node(adr);
	if (!*g_memory)
	{
		*g_memory = node;
		return (g_memory);
	}
	tmp = *g_memory;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (g_memory);
}

/*Cette fonction alloue dynamiquement de la mémoire pour un bloc de mémoire 
de taille size. Si l'allocation réussit, la fonction appelle add_adr pour 
ajouter l'adresse de ce bloc à la liste gérée par g_memory. Elle renvoie 
ensuite l'adresse du bloc alloué.*/

void	*memory_adr(t_alloc **g_memory, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	else
		return (add_adr(g_memory, ptr), ptr);
}

/*Cette fonction est utilisée pour libérer la mémoire allouée dynamiquement,
notamment pour libérer les blocs de mémoire précédemment alloués à l'aide 
de memory_adr.*/

void	free_memory(t_alloc **g_memory, t_alloc *node)
{
	if (!node)
		return ;
	free_memory(g_memory, node->next);
	free(node->adr);
	free(node);
}

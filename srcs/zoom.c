/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:36:54 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/20 14:36:58 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Fonction pour zoomer sur la fenêtre
void zoom(t_data *data, double factor)
{
    // Augmenter ou réduire la taille de la zone visible
    data->zoom_factor *= factor;

    // Redessiner la scène avec le nouveau niveau de zoom
    redraw_scene(data);
}

// Fonction pour redessiner la scène avec le nouveau niveau de zoom
void redraw_scene(t_data *data)
{
    // Effacer la fenêtre
    clear_window(data);

    // Dessiner la scène avec les nouvelles transformations de zoom
    draw_scene(data);
}

// Fonction pour dessiner la scène avec les transformations de zoom appliquées
void draw_scene(t_data *data)
{
    // Transformer les coordonnées des objets en fonction du niveau de zoom
    // Dessiner les objets dans la fenêtre en utilisant les nouvelles coordonnées
}
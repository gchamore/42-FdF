/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:40:16 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/19 16:40:34 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

//Original function that handles key press events
void OnKeyPress(Key key)
{
    // Display a message
    DisplayMessage("You pressed the key: " + key);
}

// Hook function that intercepts key press events
void Hooked_OnKeyPress(Key key)
{
    // Perform additional behavior
    ChangeMessageColor(Color.Red);
    PlaySound("beep.wav");

    // Pass the event along to the original function
    OnKeyPress(key);
}

// Hook the OnKeyPress function
void HookOnKeyPress()
{
    // Replace the OnKeyPress function with our hook function
    OnKeyPress = Hooked_OnKeyPress;
}

// Main program loop
void Main()
{
    // Hook the OnKeyPress function
    HookOnKeyPress();

    // Wait for key press events
    while (true)
    {
        Key key = WaitForKeyPress();
        OnKeyPress(key);
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reminder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:19:55 by afoth             #+#    #+#             */
/*   Updated: 2025/05/13 18:19:55 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <X11/keysym.h>

/* CHANGE FOR TIME TO POPUP IN MINUTES */
#define POPUPTIME 30

/* Change for POPUP size */
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 800

/* Messages (add more lines in print_message if needed) */
#define MESSAGE  "Hello, are you still working?"
#define MESSAGE2 "If so press 'y'"
#define MESSAGE3 "else get back to work! You got this!"
#define MESSAGE4 "(to close program press esc)"

typedef struct s_mlx
{
	void	*connection;
	void	*window;
	int		width;
	int		height;
}	t_mlx;

int	ft_close_window(t_mlx *mlx)
{
	if (mlx->window)
		mlx_destroy_window(mlx->connection, mlx->window);
	if (mlx->connection)
	{
		mlx_destroy_display(mlx->connection);
		free(mlx->connection);
	}
	free(mlx);
	exit(0);
	return (0);
}
//Keypresses are handled with the X11/keysym.h lib
int	keypress(int keycode, t_mlx *mlx)
{
	// printf("Key pressed: %d\n", keycode); // Uncomment for debugging keycodes
	if (keycode == XK_y) // 'y'
	{
		mlx_destroy_window(mlx->connection, mlx->window);
		mlx_loop_end(mlx->connection);
		return (1);
	}
	else if (keycode == XK_Escape) // ESC
	{
		ft_close_window(mlx);
	}
	return (0);
}

void	print_message(t_mlx *mlx)
{
	int	x;
	int	y;

	x = SCREEN_WIDTH / 2 - (strlen(MESSAGE) * 5);
	y = SCREEN_HEIGHT / 2;
	mlx_string_put(mlx->connection, mlx->window, x, y,        0xFFFFFF, MESSAGE);
	mlx_string_put(mlx->connection, mlx->window, x, y + 30,   0xAAAAAA, MESSAGE2);
	mlx_string_put(mlx->connection, mlx->window, x, y + 60,   0xAAAAAA, MESSAGE3);
	mlx_string_put(mlx->connection, mlx->window, x, y + 120,   0xAAAAAA, MESSAGE4);
}

void	show_reminder(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		exit(1);
	mlx->width = SCREEN_WIDTH;
	mlx->height = SCREEN_HEIGHT;
	mlx->connection = mlx_init();
	if (!mlx->connection)
	{
		free(mlx);
		exit(1);
	}
	mlx->window = mlx_new_window(mlx->connection, mlx->width, mlx->height, "Reminder");
	if (!mlx->window)
	{
		mlx_destroy_display(mlx->connection);
		free(mlx->connection);
		free(mlx);
		exit(1);
	}
	print_message(mlx);
	mlx_hook(mlx->window, 2, 1L << 0, keypress, mlx);
	mlx_hook(mlx->window, 17, 0, ft_close_window, mlx);
	mlx_loop(mlx->connection);
	mlx_destroy_display(mlx->connection);
	free(mlx->connection);
	free(mlx);
}

int	main(void)
{
	printf("Program Reminder_exe started,\nif you want to be able to close the terminal run the program like this: ./Reminder_exe & disown\n");
	while (1)
	{
		// sleep(5); //for quick debuging, carefull can open a lot of windows!
		sleep(POPUPTIME * 60); //comment out for quick debuging
		show_reminder(); // Blocks until 'y' or ESC
	}
	return (0);
}

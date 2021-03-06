/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enunes <eocnunes@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 14:43:43 by enunes            #+#    #+#             */
/*   Updated: 2017/09/25 14:36:30 by enunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*parse_flags(char **format, t_handler *h)
{
	if (is_flag(**format))
	{
		if (**format == '#')
			h->hash = 1;
		else if (**format == '0')
			h->zero = 1;
		else if (**format == '-')
			h->minus = 1;
		else if (**format == '+')
			h->plus = 1;
		else if (**format == ' ')
			h->space = 1;
		*format++;
		return (parse_flags(format, h));
	}
	else
		return (*format);
}

char	*parse_width(char **format, t_handler *h)
{
	while (is_num(**format) || **format = '*')
	{
		if (is_num(**format))
		{
			h->width = ft_atoi(*format);
			while (is_num(**format))
				*format++;
		}
		if (**format == '*')
		{
			h->width = va_arg(h->ap, int);
			if (h->width < 0)
			{
				h->minus = 1;
				h->width = (h->width * -1);
			}
			*format++;
		}
	}
	return (*format);
}

char	*parse_prec(char **format, t_handler *h)
{
	if (**format == '.')
	{
		*format++;
		if (**format == '*')
		{
			h->prec = va_arg(h->ap, int);
			if (f->prec < 0)
				f->prec = -1;
			*format++;
			return (*format);
		}
		else if (is_num(**format))
		{
			f->prec = ft_atoi(*format);
			
			if (f->prec < 0)
				return (0);
		}
		else
			f->prec = 0;
		return (*format);
		f->prec = -1;
	}
	else
		return (*format);
}

char	*parse_mod(char **format, t_handler *h)
{
	if (is_mod(**format))
	{
		if (**format == 'h' && *(*format + 1) == 'h')
		{
			h->hh = 1;
			*format++;
		}
		else if (**format == 'h')
			h->h = 1;
		else if (**format == 'l' && *(*format + 1) == 'l')
		{
			h->ll = 1;
			*format++;
		}
		else if (**format == 'l')
			h->l = 1;
		else if (**format == 'j')
			h->j = 1;
		else if (**format == 'z')
			h->z = 1;
		*format++;
	}
	return (*format);
}

char	*parse_specifier(char *fmt, t_handler *h)
{
	if (**format == 's' || **format == 'S')
		s_conv(**format, h);
	else if (**format == 'p')
		p_conv(h);
	else if (**format == 'd' || **format == 'D' || **format == 'i')
		d_conv(**format, h);
	else if (**format == 'o' || **format == 'O')
		o_conv(**format, h);
	else if (**format == 'u' || **format == 'U')
		u_conv(**format, h);
	else if (**format == 'x' || **format == 'X')
		x_conv(**format, h);
	else if (**format == 'c' || **format == 'C')
		c_cconv(**format, h);
	else if (**format == '%')
		percent_conv(h);
	else
		notype(**format, h);
}

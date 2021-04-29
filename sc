	if (ft_strchr("\"'", *(*current)))
	{
		quote = (*current);
		(*current)++;
		while (*(*current) != *quote || *skip)
		{
			*skip = 0;
			if (*(*current) == 0)
				return (NULL);
			if ((*current)[0] == '\\' && (*current)[1] == '\\')
				(*current) += 2;
			else
			{
				*skip = (*quote != '\'' && *(*current) == '\\'
						&& (*current)[1] == *quote);
				(*current)++;				
			}
		}
		(*current)++;
	}
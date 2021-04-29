	if (!*(*quote) && (ft_strchr("\"'", *(*ref))
	&& (*ref) != command && (*ref)[-1] != '\\'))
		(*quote) = (*ref);
	else if (*(*quote) == *(*ref))
		(*quote) = "\0";
	len = wildcard_len((*ref));
	if (len && *(*quote) != '\'')
		(*ref) += add_wildcard((*ref), len, alst);
	else if (*(*quote) != '\'' && *(*ref) == '$'
	&& ((*ref) == command || (*ref)[-1] != '\\'))
		(*ref) += add_env((*ref), alst);
	else
		ft_lstadd_back((t_list **)alst, ft_strndup((*ref)++, 1));
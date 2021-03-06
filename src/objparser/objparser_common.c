/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser_common.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

t_bool  objparser_eos(t_objparser_ctx *ctx)
{
    return (ctx->invalid || ctx->current == ctx->end);
}

t_bool  objparser_isvalid(t_objparser_ctx *ctx)
{
    return (ctx->current <= ctx->end);
}

void    objparser_skip_ws(t_objparser_ctx *ctx)
{
    assert(objparser_isvalid(ctx));
    if (objparser_eos(ctx))
        return ;
    while (ctx->current < ctx->end && ft_isws(*ctx->current))
        ctx->current++;
}

void    objparser_skip_until_nl(t_objparser_ctx *ctx)
{
    assert(objparser_isvalid(ctx));
    if (objparser_eos(ctx))
        return ;
    while (ctx->current < ctx->end && *ctx->current != '\n')
        ctx->current++;
}

/*
 * Copyright (c) 2014, Mentor Graphics Corporation
 * Copyright (c) 2015 Xilinx, Inc.
 * Copyright (c) 2016 Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "rpmsg_lite.h"
#include "rpmsg_queue.h"

typedef struct
{
    unsigned long src;
    void *data;
    short int len;
} rpmsg_queue_rx_cb_data_t;

extern volatile struct rpmsg_lite_instance rpmsg_lite_dev;

int rpmsg_queue_rx_cb(void *payload, int payload_len, unsigned long src, void *priv)
{
    rpmsg_queue_rx_cb_data_t msg;

    RL_ASSERT(priv);

    msg.data = payload;
    msg.len = payload_len;
    msg.src = src;

    /* if message is successfully added into queue then hold rpmsg buffer */
    if (env_put_queue(priv, &msg, 0))
    {
        /* hold the rx buffer */
        return RL_HOLD;
    }

    return RL_RELEASE;
}

rpmsg_queue_handle rpmsg_queue_create(struct rpmsg_lite_instance *rpmsg_lite_dev)
{
    int status = -1;
    void *q = NULL;

    if (rpmsg_lite_dev == RL_NULL)
        return RL_NULL;

    /* create message queue for channel default endpoint */
    status = env_create_queue(&q, rpmsg_lite_dev->rvq->vq_nentries, sizeof(rpmsg_queue_rx_cb_data_t));
    if ((status) || (q == NULL))
    {
        return RL_NULL;
    }

    return ((rpmsg_queue_handle)q);
}

int rpmsg_queue_destroy(struct rpmsg_lite_instance *rpmsg_lite_dev, rpmsg_queue_handle q)
{
    if (rpmsg_lite_dev == RL_NULL)
        return RL_ERR_PARAM;

    if (q == RL_NULL)
        return RL_ERR_PARAM;
    env_delete_queue((void *)q);
    return RL_SUCCESS;
}

int rpmsg_queue_recv(struct rpmsg_lite_instance *rpmsg_lite_dev,
                     rpmsg_queue_handle q,
                     unsigned long *src,
                     char *data,
                     int maxlen,
                     int *len,
                     unsigned long timeout)
{
    rpmsg_queue_rx_cb_data_t msg;
    int retval = RL_SUCCESS;

    if (!rpmsg_lite_dev)
        return RL_ERR_PARAM;
    if (!q)
        return RL_ERR_PARAM;
    if (!data)
        return RL_ERR_PARAM;

    /* Get an element out of the message queue for the selected endpoint */
    if (env_get_queue((void *)q, &msg, timeout))
    {
        if (src != NULL)
            *src = msg.src;
        if (len != NULL)
            *len = msg.len;

        if (maxlen >= msg.len)
        {
            env_memcpy(data, msg.data, msg.len);
        }
        else
        {
            retval = RL_ERR_BUFF_SIZE;
        }

        /* Return used buffers. */
        rpmsg_lite_release_rx_buffer(rpmsg_lite_dev, msg.data);

        return retval;
    }
    else
    {
        return RL_ERR_NO_BUFF; /* failed */
    }
}

int rpmsg_queue_recv_nocopy(struct rpmsg_lite_instance *rpmsg_lite_dev,
                            rpmsg_queue_handle q,
                            unsigned long *src,
                            char **data,
                            int *len,
                            unsigned long timeout)
{
    rpmsg_queue_rx_cb_data_t msg;

    if (!rpmsg_lite_dev)
        return RL_ERR_PARAM;
    if (!data)
        return RL_ERR_PARAM;
    if (!q)
        return RL_ERR_PARAM;

    /* Get an element out of the message queue for the selected endpoint */
    if (env_get_queue((void *)q, &msg, timeout))
    {
        if (src != NULL)
            *src = msg.src;
        if (len != NULL)
            *len = msg.len;

        *data = msg.data;

        return RL_SUCCESS; /* success */
    }

    return RL_ERR_NO_BUFF; /* failed */
}

int rpmsg_queue_nocopy_free(struct rpmsg_lite_instance *rpmsg_lite_dev, void *data)
{
    if (!data)
        return RL_ERR_PARAM;

    /* Return used buffer. */
    rpmsg_lite_release_rx_buffer(rpmsg_lite_dev, data);

    return RL_SUCCESS;
}

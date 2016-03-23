/* Copyright (c) 2001 Matej Pfajfar.
 * Copyright (c) 2001-2004, Roger Dingledine.
 * Copyright (c) 2004-2006, Roger Dingledine, Nick Mathewson.
 * Copyright (c) 2007-2013, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file circuitstats.h
 * \brief Header file for circuitstats.c
 **/

#ifndef TOR_CIRCUITSTATS_H
#define TOR_CIRCUITSTATS_H

extern circuit_build_times_t circ_times;

int circuit_build_times_disabled(void);
int circuit_build_times_enough_to_compute(circuit_build_times_t *cbt);
void circuit_build_times_update_state(circuit_build_times_t *cbt,
                                      or_state_t *state);
int circuit_build_times_parse_state(circuit_build_times_t *cbt,
                                    or_state_t *state);
void circuit_build_times_count_timeout(circuit_build_times_t *cbt,
                                       int did_onehop);
int circuit_build_times_count_close(circuit_build_times_t *cbt,
                                    int did_onehop, time_t start_time);
void circuit_build_times_set_timeout(circuit_build_times_t *cbt);
int circuit_build_times_add_time(circuit_build_times_t *cbt,
                                 build_time_t time);
int circuit_build_times_needs_circuits(circuit_build_times_t *cbt);

int circuit_build_times_needs_circuits_now(circuit_build_times_t *cbt);
void circuit_build_times_init(circuit_build_times_t *cbt);
void circuit_build_times_free_timeouts(circuit_build_times_t *cbt);
void circuit_build_times_new_consensus_params(circuit_build_times_t *cbt,
                                              networkstatus_t *ns);
double circuit_build_times_timeout_rate(const circuit_build_times_t *cbt);
double circuit_build_times_close_rate(const circuit_build_times_t *cbt);

#ifdef CIRCUITSTATS_PRIVATE
double circuit_build_times_calculate_timeout(circuit_build_times_t *cbt,
                                             double quantile);
build_time_t circuit_build_times_generate_sample(circuit_build_times_t *cbt,
                                                 double q_lo, double q_hi);
void circuit_build_times_initial_alpha(circuit_build_times_t *cbt,
                                       double quantile, double time_ms);
int circuit_build_times_update_alpha(circuit_build_times_t *cbt);
double circuit_build_times_cdf(circuit_build_times_t *cbt, double x);
void circuitbuild_running_unit_tests(void);
void circuit_build_times_reset(circuit_build_times_t *cbt);

/* Network liveness functions */
int circuit_build_times_network_check_changed(circuit_build_times_t *cbt);
#endif

/* Network liveness functions */
void circuit_build_times_network_is_live(circuit_build_times_t *cbt);
int circuit_build_times_network_check_live(circuit_build_times_t *cbt);
void circuit_build_times_network_circ_success(circuit_build_times_t *cbt);

/* DOCDOC circuit_build_times_get_bw_scale */
int circuit_build_times_get_bw_scale(networkstatus_t *ns);

#endif


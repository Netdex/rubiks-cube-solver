#ifndef CLUSTER_H
#define CLUSTER_H

#include "cv/color.h"

/*
 * whether we should continue k-means or not.
 * @param k             number of clusters
 * @param its           iterations completed
 * @param iter          maximum iterations
 * @param e             minimum epsilon required
 * @param old_centroids previous iteration's centroids
 * @param centroids     current iteration's centroids
 * @return              whether we should continue k-means
 */
static bool cluster_rgb_continue(int k, int its, int iter, float e, rgb_t old_centroids[], rgb_t centroids[]);

/*
 * cluster colors by k-means, into k clusters
 * @param k         number of clusters
 * @param e         minimum epsilon required between continugous centroids
 * @param iter      maximum iterations of algorithm
 * @param colors    dataset
 * @param n         size of dataset
 * @param centroids pointer to length k array to store centroids
 */
void cluster_rgb_kmeans(int k, float e, int iter, rgb_t colors[], int n, rgb_t *centroids);

/*
 * label clusters by centroids
 * @param k         number of clusters
 * @param colors    dataset
 * @param n         size of dataset
 * @param centroids centroids with which to label data
 * @param labels    pointer to length n array to store labels
 */
void cluster_rgb_label(int k, rgb_t colors[], int n, rgb_t centroids[], int *labels);

/*
 * find data point label
 * @param k         number of clusters
 * @param color     data point
 * @param centroids centroids to label data
 * @param label     chosen label
 */
void cluster_rgb_min_dist(int k, rgb_t color, rgb_t centroids[], int *label);

/*
 * find centroids of labelled dataset
 * @param k         number of clusters
 * @param colors    dataset
 * @param n         size of dataset
 * @param labels    assigned labels for dataset
 * @param centroids pointer to length k array to store centroids
 */
void cluster_rgb_centroids(int k, rgb_t colors[], int n, int labels[], rgb_t *centroids);


#endif
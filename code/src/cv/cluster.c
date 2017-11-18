#include "stdafx.h"

#include "cv/cluster.h"

bool cluster_rgb_continue(int k, int its, int iter, float e, rgb_t old_centroids[], rgb_t centroids[]){
    // check we haven't reached max iterations
    if(its >= iter) return false;

    // check that delta centroid is bigger than epsilon
    for(int i = 0; i < k; i++){
        if(fabsf(old_centroids[i].r - centroids[i].r) > e
            || fabsf(old_centroids[i].g - centroids[i].g) > e
            || fabsf(old_centroids[i].b - centroids[i].b) > e)
                return true;
    }
    return false;
}

void cluster_rgb_kmeans(int k, float e, int iter, rgb_t colors[], int n, rgb_t *centroids){
    srand((unsigned int)time(NULL));
    
    rgb_t *old_centroids = (rgb_t*)calloc(k, sizeof(rgb_t));
    
    // random init centroids
    for(int i = 0; i < k; i++){
        rgb_t *ct = centroids + i;
        ct->r = randf();
        ct->g = randf();
        ct->b = randf();
    }

    int its = 0;
    int *labels = (int*)calloc(n, sizeof(int));
    do {
        memcpy(old_centroids, centroids, sizeof(rgb_t) * k);
        its++;
        cluster_rgb_label(k, colors, n, centroids, labels);
        cluster_rgb_centroids(k, colors, n, labels, centroids);
    } while(cluster_rgb_continue(k, its, iter, e, old_centroids, centroids));

    LOG("clustering completed after %d iters", its);
    
    free(old_centroids);
    free(labels);
}

void cluster_rgb_label(int k, rgb_t colors[], int n, rgb_t centroids[], int *labels){
    for(int i = 0; i < n; i++){
        rgb_t *color = colors + i;
        cluster_rgb_min_dist(k, *color, centroids, labels + i);
    }
}

void cluster_rgb_min_dist(int k, rgb_t color, rgb_t centroids[], int *label){
    float minDist = FLT_MAX;
    *label = 0;
    for(int i = 0; i < k; i++){
        rgb_t *centroid = centroids + i;
        float dist = color_rgb_dist_sq(color, *centroid);
        if(dist < minDist){
            minDist = dist;
            *label = i;
        }
    }
}

void cluster_rgb_centroids(int k, rgb_t colors[], int n, int labels[], rgb_t *centroids){
    int *count = (int*) calloc(k, sizeof(int));
    rgb_t *lsum = (rgb_t*) calloc(k, sizeof(rgb_t));

    // initialize structures to empty
    for(int i = 0; i < k; i++){
        count[i] = 0;
        lsum[i].r = 0.f;
        lsum[i].g = 0.f;
        lsum[i].b = 0.f;
    }
    
    // add values and count number of labels for each centroid
    for(int i = 0; i < n; i++){
        rgb_t *color = colors + i;
        int label = labels[i];
        
        count[label] += 1;
        lsum[label].r += color->r;
        lsum[label].g += color->g;
        lsum[label].b += color->b;
    }
   
    for(int i = 0; i < k; i++){
        rgb_t *ct = centroids + i;
        
        if(count[i] == 0){
             // if centroid has no labels, randomize
            ct->r = randf();
            ct->g = randf();
            ct->b = randf();
        } else {
            // set centroid to mean of dataset
            float invc = 1.0f / count[i];
            ct->r = lsum[i].r * invc;
            ct->g = lsum[i].g * invc;
            ct->b = lsum[i].b * invc;
        }
    }
    free(lsum);
    free(count);
}
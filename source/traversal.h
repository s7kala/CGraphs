#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "graphimpl.h"

void weighted_shortest_path(const GraphImpl& gp, const Vector& v1, const Vector& v2, std::vector<std::string> &path);
void unweighted_shortest_path(const GraphImpl& gp, const Vector& v1, const Vector& v2, std::vector<std::string> &path);

#endif
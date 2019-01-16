cmake_minimum_required(VERSION 3.13)
project(newProj)

set(CMAKE_CXX_STANDARD 14)

add_executable(newProj main.cpp Searchable.h Point.h Matrix.h CashManager.h FileCacheManager.h Solver.h Searcher.h Bestfs.h SolverSearchAdapter.h ClientHandler.h MyMatrixClientHandler.h BFS.h DFS.h Astar.h State.h Server.h MyParallelServer.h Tester.h)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const int POINT_RADIUS = 5;
    const int STROKE_WEIGHT = 3;

    SDL_Window* window = SDL_CreateWindow("QuadTree", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Rectangle boundary(0, 0, WIDTH, HEIGHT);
    QuadTree qtree(boundary, 4);

    std::vector<Point> points;
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist_x(0, WIDTH);
    std::uniform_int_distribution<int> dist_y(0, HEIGHT);

    for (int i = 0; i < 50; i++) {
        Point point(dist_x(rng), dist_y(rng));
        points.push_back(point);
        qtree.insert(point);
    }

    bool running = true;
    SDL_Event event;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for (const auto& point : points) {
            point.draw(renderer, POINT_RADIUS);
        }
        qtree.draw(renderer, STROKE_WEIGHT);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

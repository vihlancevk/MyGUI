#ifndef FILTER_HPP_
#define FILTER_HPP_

class Filter {
    public:
        Filter(): {}

        virtual void actionWithCanvas(sf::VertexArray&,
                                      unsigned, unsigned, unsigned, unsigned,
                                      unsigned, unsigned) {}

        virtual ~Filter() = default;
};

#endif // FILTER_HPP_

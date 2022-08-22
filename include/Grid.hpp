#ifndef GRID_HPP_
#define GRID_HPP_


#include <vector>
#include <ostream>
#include <cstdint>
#include <climits>


/**
 * @brief Class for the main playing board
 */
class Grid
{
    public:
        /**< Types of player markers */
        enum PlayerMark {GRID_TYPE_NONE = 0, GRID_TYPE_RED = INT_MIN, GRID_TYPE_YELLOW = INT_MAX};

        static const uint8_t SCuyHeight = 6;        /**< Height of the grid */
        static const uint8_t SCuyWidth = 7;         /**< Width of the grid */
        static const uint8_t SCuyNumberToMatch = 4; /**< Number of markers in a row that must be achieved */

        /* Getters */
        const std::vector<std::vector<PlayerMark> >& getCells() const noexcept;
        int8_t getNextCell(uint8_t uyColumn) const noexcept;

        explicit Grid() noexcept;   /**< Default constructor */

        /**
         * @brief Gets the mark of the next player
         * 
         * @param CEplayerMark the mark of the current player
         * @return PlayerMark the mark of the next player
         */
        static PlayerMark nextPlayer(const PlayerMark& CEplayerMark) noexcept;

        const std::vector<PlayerMark>& operator [](uint8_t uyIndex) const noexcept; /**< Bracket operator */

        /**
         * @brief Makes a play in the grid
         * 
         * @param CEplayerMark the mark of the player that makes the play
         * @param uyPlayColumn the chosen column for the play
         */
        void makePlay(const PlayerMark& CEplayerMark, uint8_t uyPlayColumn);

        /**
         * @brief Checks if a play would be valid
         * 
         * @param uyPlayColumn the chosen column for the play
         * @return true if the play is valid
         * @return false if the play is invalid
         */
        bool isValidPlay(uint8_t uyPlayColumn) const noexcept;

        /**
         * @brief Checks if the game has been won
         * 
         * @return PlayerMark the mark of the player that won
         */
        PlayerMark checkWinner() const noexcept;

    private:
        std::vector<std::vector<PlayerMark> > _a2playerMarkCells;   /**< A matrix of markers representing the board */
        std::vector<int8_t> _ayNextCell;    /**< Indicates the next playable cell in a column */
        PlayerMark _EplayerMarkWinner;       /**< The marker of the player who won the game */

        /**
         * @brief Checks if a given play has won the game
         * 
         * @param CEplayerMark the mark of the player that made the previous play
         * @param yPlayColumn the chosen column for the play
         * @return true if the play won the game
         * @return false if the play did not win the game
         */
        bool isWinnerPlay(const PlayerMark& CEplayerMark, int8_t yPlayColumn) noexcept;

};


inline const std::vector<std::vector<Grid::PlayerMark> >& Grid::getCells() const noexcept 
{ return _a2playerMarkCells; }
inline int8_t Grid::getNextCell(uint8_t uyColumn) const noexcept { return _ayNextCell[uyColumn]; }


inline const std::vector<Grid::PlayerMark>& Grid::operator [](uint8_t uyIndex) const noexcept 
{ return _a2playerMarkCells[uyIndex]; }

inline bool operator ==(const Grid& Cgrid1, const Grid& Cgrid2) noexcept
{ return Cgrid1.getCells() == Cgrid2.getCells(); }

inline Grid::PlayerMark Grid::checkWinner() const noexcept { return _EplayerMarkWinner; }


/* Stream insertion operator overloads */
std::ostream& operator <<(std::ostream& ostream, const Grid::PlayerMark& CEplayerMark) noexcept;
std::ostream& operator <<(std::ostream& ostream, const Grid& Cgrid) noexcept;


#endif
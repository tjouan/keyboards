module Keyboards
  class Layout
    Cut = Struct.new(:x, :y, :width, :height)

    class CutLayout
      WIDTH     = 2890
      HEIGHT    = 1600
      ORIGIN_X  = 250
      ORIGIN_Y  = 100
      COLUMNS   = 14
      ROWS      = 6
      CUT_SIZE  = 140
      CUT_SPACE = 50

      def width
        WIDTH
      end

      def height
        HEIGHT
      end

      def cuts
        (0..(ROWS - 1)).flat_map do |row_index|
          (0..(COLUMNS - 1)).map do |col_index|
            x = col_index * (CUT_SIZE + CUT_SPACE) + ORIGIN_X
            y = row_index * (CUT_SIZE + CUT_SPACE) + ORIGIN_Y
            Cut.new(x, y, CUT_SIZE, CUT_SIZE)
          end
        end
      end
    end
  end
end

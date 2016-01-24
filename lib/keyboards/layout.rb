module Keyboards
  class Layout
    Cut = Struct.new(:x, :y, :width, :height)

    class CutLayout
      WIDTH         = 2890
      HEIGHT        = 1600
      COLUMNS       = 14
      ROWS          = 6
      CUT_SIZE      = 140
      CUT_SPACE     = 50
      CASE_PADDING  = [70, 70, 70, 200].freeze

      def width
        WIDTH
      end

      def height
        HEIGHT
      end

      def cuts
        [*switch_cuts, case_cut]
      end

    protected

      def case_cut
        switch_cut_row_last = switch_cuts.max_by &:x
        switch_cut_col_last = switch_cuts.max_by &:y
        Cut.new(
          0, 0,
          switch_cut_row_last.x + switch_cut_row_last.width + CASE_PADDING[1],
          switch_cut_col_last.y + switch_cut_col_last.height + CASE_PADDING[2]
        )
      end

      def switch_cuts
        (0..(ROWS - 1)).flat_map do |row_index|
          (0..(COLUMNS - 1)).map do |col_index|
            x = col_index * (CUT_SIZE + CUT_SPACE) + CASE_PADDING[3]
            y = row_index * (CUT_SIZE + CUT_SPACE) + CASE_PADDING[0]
            Cut.new(x, y, CUT_SIZE, CUT_SIZE)
          end
        end
      end
    end
  end
end

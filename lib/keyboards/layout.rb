module Keyboards
  class Layout
    WIDTH           = 2890
    HEIGHT          = 1600
    U               = 190
    SWITCH_SIZE     = 140
    CASE_PADDING    = [300, 50, 50, 50].freeze

    class << self
      def ukbd63l_mk2
        layout = new
        layout.grid [1, 0], [5, 5]
        layout.key [0, 0], u: 1
        layout.key [0, 1], :vertical, u: 2
        layout.key [0, 3], :vertical, u: 2
        layout.keys [0, 5], u: [1.5, 1.75, 1.75]
        layout.key [6, 0], :vertical, u: 2
        layout.key [6, 2], :vertical, u: 2
        layout.key [6, 4], u: 2
        layout.grid [7, 0], [7, 3]
        layout.grid [7, 3], [6, 1]
        layout.grid [9, 4], [4, 1]
        layout.grid [9, 5], [2, 1]
        layout.key [13, 3], :vertical, u: 2
        layout
      end
    end

    def initialize
      @keys  = []
      @rects = []
    end

    def width
      WIDTH
    end

    def height
      HEIGHT
    end

    def key origin, direction = :horizontal, u: 1
      @keys << Key.new(*origin, u, direction)
    end

    def keys origin, direction = :horizontal, u:
      offset_x, offset_y = 0, 0
      u.each do |ku|
        x, y = origin
        @keys << Key.new(x + offset_x, y + offset_y, ku, direction)
        if direction == :horizontal
          offset_x += ku
        else
          offset_y += ku
        end
      end
    end

    def grid origin, size
      gox, goy = origin
      gsx, gsy = size
      (gox..(gox + gsx - 1)).each do |ox|
        (goy..(goy + gsy - 1)).each do |oy|
          key [ox, oy]
        end
      end
    end

    def max_x
      @keys.map do |k|
        k.urect.x + k.urect.width
      end.max
    end

    def max_y
      @keys.map do |k|
        k.urect.y + k.urect.height
      end.max
    end

    def rects
      @keys.flat_map do |key|
        [key.urect, key.switch, key.keycap]
      end + [
        Rect.new(
          0,
          0,
          max_x + CASE_PADDING[1],
          max_y + CASE_PADDING[2],
          :black
        )
      ]
    end

  private

    class Key < Struct.new :x, :y, :u, :direction
      def urect
        Rect.new(
          x * U + CASE_PADDING[3],
          y * U + CASE_PADDING[0],
          U * (direction == :horizontal ? u : 1),
          U * (direction == :vertical ? u : 1),
          :blue
        )
      end

      def switch
        cx, cy = urect.center
        Rect.new(
          cx - SWITCH_SIZE / 2,
          cy - SWITCH_SIZE / 2,
          SWITCH_SIZE,
          SWITCH_SIZE,
          :red
        )
      end

      def keycap
        Rect.new(
          urect.x + 5,
          urect.y + 5,
          urect.width - 5 * 2,
          urect.height - 5 * 2,
          :green
        )
      end
    end

    class Rect < Struct.new :x, :y, :width, :height, :color
      def center
        [x + (width / 2), y + (height / 2)]
      end
    end
  end
end

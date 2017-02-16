require 'embed_utils/rake_task'

require 'keyboards'

BUILD_DIR   = 'build'.freeze
LAYOUT_CUT  = "#{BUILD_DIR}/layout_cut.svg".freeze


file LAYOUT_CUT do |t|
  layout = Keyboards::Layout::CutLayout.new
  File.open t.name, ?w do |f|
    f.write Keyboards::Template.render(
      t.name.sub("#{BUILD_DIR}/", ''),
      layout: layout
    )
  end
end


task default: :hex

EmbedUtils::RakeTask.new do |t|
  t.board     = :micro
  t.libraries += %w[HID Keyboard]
  t.options   << "-Iinclude/#{ENV.fetch 'KEYBOARD', 'ukbd63l-mk1'}"
end

desc 'Build the layout cutting template'
task layout: LAYOUT_CUT

require 'embed_utils/rake_task'

require 'keyboards'

BUILD_DIR   = 'build'.freeze
CXX         = 'c++'.freeze
TEST_DIR    = "#{BUILD_DIR}/test".freeze
TEST_RUNNER = "#{TEST_DIR}/run".freeze
TEST_OBJS   = FileList['test/*_test.cpp'].pathmap "%{^test,#{TEST_DIR}}X.o"
TEST_SRC    = -> t { t.pathmap "%{^#{TEST_DIR},test}X.cpp" }
TEST_SOBJ   = -> t { t.sub '_test', '' }
TEST_SSRC   = -> t { t.pathmap "%{^#{TEST_DIR},src}X.cpp" }
CHECK_LOC   = ENV.fetch('UKBD_CHECK_LOC', '/usr/local').freeze
LAYOUT_CUT  = "#{BUILD_DIR}/layout_cut.svg".freeze


file TEST_RUNNER => TEST_OBJS do |t|
  sh "#{CXX} -L#{CHECK_LOC}/lib -o #{t.name} #{t.prerequisites.join ' '} -lcheck"
end

rule /#{TEST_DIR}\/.+_test\.o$/ => [TEST_SRC, TEST_SOBJ, TEST_DIR] do |t|
  sh "#{CXX} -Iinclude -I#{CHECK_LOC}/include #{t.source} -c -o #{t.name}"
end

rule /#{TEST_DIR}\/.+\.o$/ => [TEST_SSRC, TEST_DIR] do |t|
  sh "#{CXX} -Iinclude #{t.source} -c -o #{t.name}"
end

directory TEST_DIR

file LAYOUT_CUT do |t|
  layout = Keyboards::Layout::CutLayout.new
  File.open t.name, ?w do |f|
    f.write Keyboards::Template.render(
      t.name.sub("#{BUILD_DIR}/", ''),
      layout: layout
    )
  end
end


task default: :test

# FIXME: build task should depend on configuration in headers too
EmbedUtils::RakeTask.new do |t|
  t.board     = :micro
  t.libraries += %w[HID Keyboard]
  t.options   << "-Iinclude/#{ENV.fetch 'KEYBOARD', 'ukbd63l-mk1'}"
  t.options   << '-DUKBD_DEBUG_SERIAL' if ENV.key? 'DEBUG'
end

desc 'Build the layout cutting template'
task layout: LAYOUT_CUT

desc 'Run firmware tests'
task test: TEST_RUNNER do
  exec "#{TEST_DIR}/run"
end

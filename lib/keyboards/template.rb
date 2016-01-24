require 'erb'
require 'pathname'

module Keyboards
  class Template
    SEARCH_PATH = Pathname.new('templates').freeze

    class << self
      def render template_name, variables = {}
        path = SEARCH_PATH + Pathname.new("#{template_name}.erb")
        tpl = ERB.new(File.read(path), nil, ?-)
        tpl.filename = path.to_s
        tpl.result build_erb_binding variables
      end

    protected

      def build_erb_binding variables
        Object.new.instance_eval do |o|
          variables.each do |k, v|
            o.instance_variable_set "@#{k}", v
          end
          binding
        end
      end
    end
  end
end

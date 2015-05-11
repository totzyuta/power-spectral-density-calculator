require 'csv'

class Normalizer
  def initialize()
  end

  def normalize(data)
    i=0
    first = []
    symbol = []
    second = []
    result = []
    data.each do |d|
      first[i] = d.sub(/E(\+|-)\d\d/, "")
      symbol[i] = d.sub(/.(\d+.\d+)E/, "").sub(/\d\d\s\s/, "")
      second[i] = d.sub(/.(\d+.\d+)E/, "")

      first[i].to_f
      second[i].to_f
      if symbol[i] = '+' then
        result[i] = first[i].to_f * (10 ** second[i].to_f)
      elsif symbol[i] = '-' then
        result[i] = first[i].to_f * (-10 ** second[i].to_f)
      end

      p result[i]
      i = i + 1
    end

    return result

  end
end




file_name = ARGV[0]
@data = File.open(file_name).readlines

result = []
my_normalizer = Normalizer.new() 
result = my_normalizer.normalize(@data)

CSV.open("data-normalized", 'w') do | writer |
  result.each do | item |
    writer << item
  end
end

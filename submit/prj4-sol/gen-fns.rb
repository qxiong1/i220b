#!/usr/bin/ruby

#Termination argument for call to driver function: first argument to each
#call is strictly decreasing; recursion bottoms out when first argument
#becomes 0.

NUM_MAX_ARGS = 5;
MAX_NUM_CALLS = 10;
CONST_RANGE = 10000
FUNCTION_NAME_PREFIX = 'f'

SPECIAL_OPS = [ 
  0xE8, #CALL
  0xC3, #RET_NEAR
  0xCB, #RET_FAR 
  0xC2, #RET_NEAR_WITH_POP
  0xCA, #RET_FAR_WITH_POP
]


def name(fn) "#{FUNCTION_NAME_PREFIX}#{fn}" end

def arg(i) "a#{i}" end

def rand_const() 
  n = (rand(2) > 0 ? -1 : 1)*rand(CONST_RANGE) 
  x = rand(SPECIAL_OPS.size);
  special = SPECIAL_OPS[x]
  shift = 8*rand(4)
  n &= ~((0xFF) << shift)
  n |= special << shift
  n
end

def header(fn, arity) 
  args = ((0...arity).map { |a|  "int #{arg(a)}" }).join(', ')
  "static int #{name(fn)}(#{args})"
end

def gen_declaration(fn, arities)
  arity = rand(NUM_MAX_ARGS + 1) + 1
  arities[fn] = arity
  print "#{header(fn, arity)};\n";
end

def gen_call(callerIndex, calleeIndex, arities)
  callerArity = arities[callerIndex] || 0
  calleeArity = arities[calleeIndex]
  arg0 = (callerArity > 0) ? "#{arg(0)} - #{rand(CONST_RANGE)}" : rand_const
  args = [ arg0 ]
  (1...calleeArity).each do
      argIndex = rand(2 * callerArity)
      args.push(argIndex >= callerArity ? rand_const.to_s : arg(argIndex))
  end
  "#{name(calleeIndex)}(#{args.join(', ')})"
end

def gen_definition(fn, arities)
  numFns = arities.size
  nArgs = arities[fn]
  init = rand_const
  print "#{header(fn, nArgs)}\n"
  print "{\n"
  print "  int result = #{init};\n"
  print "  if (#{arg(0)} > 0) {\n"
  (1 + rand(MAX_NUM_CALLS)).times do
    op = (rand(2) == 0) ? '+=' : '-='
    call = gen_call(fn, rand(numFns), arities)
    print "    result #{op} #{rand_const}*#{call};\n"
  end
  print "    result += #{rand_const}*#{gen_call(fn, (fn+1)%numFns, arities)};\n"
  print "  }\n"
  print "  return result;\n"
  print "}\n\n"
end

def gen_driver(driver, arities)
call = gen_call(-1, 0, arities)
print <<END_DRIVER
int 
#{driver}()
{
  return #{call};
}

END_DRIVER
end

def gen_main(driver)
print <<END_MAIN
#ifdef TEST_#{driver.upcase}

#include <stdio.h>

int main() {
  printf("%d\\n", #{driver}());
  return 0;
}

#endif //ifdef TEST_#{driver.upcase}
END_MAIN
end

def go(numFns, driver) 
  arities = { }
  numFns.times { |fn| gen_declaration(fn, arities) }
  print "\n"
  numFns.times { |fn| gen_definition(fn, arities) }
  gen_driver(driver, arities)
  gen_main(driver)
end

USAGE = "#{$0} NUM_FNS FUNCTION_NAME\n";
numFns = ARGV[0] and numFns =~ /^\d+$/ and numFns.to_i > 0 and 
  driver = ARGV[1] or abort USAGE
go(numFns.to_i, driver)
 

# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

# def configure(conf):
#     conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    module = bld.create_ns3_module('sd-manet', ['core', 'internet', 'applications', 'config-store', 'stats'])
    module.source = [
        'model/sd-manet.cc',
        'model/agent.cc',
        'model/action.cc',
        'model/action-flow.cc',
        'model/action-move.cc',
        'model/condition.cc',
        'model/condition-flow.cc',
        'model/condition-time.cc',
        'model/condition-geo.cc',
        'model/rule.cc',
        'model/controller.cc',
        'model/simple-controller.cc',
        'helper/sd-manet-helper.cc',
        ]

    module_test = bld.create_ns3_module_test_library('sd-manet')
    module_test.source = [
        'test/sd-manet-test-suite.cc',
        ]

    headers = bld(features='ns3header')
    headers.module = 'sd-manet'
    headers.source = [
        'model/sd-manet.h',
        'model/agent.h',
        'model/action.h',
        'model/action-flow.h',
        'model/action-move.h',
        'model/condition.h',
        'model/condition-flow.h',
        'model/condition-time.h',
        'model/condition-geo.h',
        'model/rule.h',
        'model/controller.h',
        'model/simple-controller.h',
        'helper/sd-manet-helper.h',
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

   # bld.ns3_python_bindings()


# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

# def configure(conf):
#     conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    module = bld.create_ns3_module('sd-manet', ['core', 'internet', 'applications', 'config-store', 'stats'])
    module.source = [
        'model/sd-manet.cc',
        'model/agent/agent.cc',
        'model/agent/action.cc',
        'model/agent/action-flow.cc',
        'model/agent/action-move.cc',
        'model/agent/condition.cc',
        'model/agent/condition-flow.cc',
        'model/agent/condition-time.cc',
        'model/agent/condition-geo.cc',
        'model/agent/rule.cc',
        'model/agent/neighbor.cc',
        'model/agent/agent-beacon.cc',
        'model/controller/controller.cc',
        'model/controller/simple-controller.cc',
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
        'model/agent/agent.h',
        'model/agent/action.h',
        'model/agent/action-flow.h',
        'model/agent/action-move.h',
        'model/agent/condition.h',
        'model/agent/condition-flow.h',
        'model/agent/condition-time.h',
        'model/agent/condition-geo.h',
        'model/agent/rule.h',
        'model/agent/neighbor.h',
        'model/agent/agent-beacon.h',
        'model/controller/controller.h',
        'model/controller/simple-controller.h',
        'helper/sd-manet-helper.h',
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

   # bld.ns3_python_bindings()


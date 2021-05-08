#pragma once

/* Copyright (C) 2021  Dhruv Chawla */
/* See LICENSE at project root for license details */

#ifndef VM2_VIRTUAL_MACHINE_HPP
#define VM2_VIRTUAL_MACHINE_HPP

#include "Module.hpp"
#include "Natives.hpp"
#include "Value.hpp"

#include <memory>
#include <unordered_map>

struct CallFrame {
    Value *stack{};
    Chunk *return_chunk{};
    Chunk::byte *return_ip{};
};

enum class ExecutionState { RUNNING = 0, FINISHED = 1 };

class VirtualMachine {
    constexpr static std::size_t stack_size = 32768;
    constexpr static std::size_t frame_size = 1024;

    Chunk::byte *ip{};

    std::unique_ptr<Value[]> stack{};
    std::size_t stack_top{};

    std::unique_ptr<CallFrame[]> frames{};
    std::size_t frame_top{};

    std::unordered_map<std::string_view, NativeFn> natives{};

    Chunk *current_chunk{};
    RuntimeModule *current_module{};

    Chunk::byte read_byte();
    std::size_t read_three_bytes();

    bool trace_stack{false};
    bool trace_insn{false};

    void push(Value value) noexcept;
    void pop() noexcept;

    std::size_t get_current_line() const noexcept;

  public:
    VirtualMachine(bool trace_stack, bool trace_insn);
    ~VirtualMachine() = default;

    VirtualMachine(const VirtualMachine &) = delete;
    VirtualMachine &operator=(const VirtualMachine &) = delete;

    void run(RuntimeModule &module);
    ExecutionState step();
};

#endif